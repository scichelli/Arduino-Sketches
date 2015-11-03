/*
 * When a box (labeled "Cookies!") is opened, play Never Gonna Give You Up
 */
#include <WaveHC.h>
#include <WaveUtil.h>

SdReader card;    // This object holds the information for the card
FatVolume vol;    // This holds the information for the partition on the card
FatReader root;   // This holds the information for the volumes root directory
FatReader file;   // This holds the information for the file we're play
WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time

uint8_t dirLevel; // indent level for file/dir names    (for prettyprinting)

#define DEBOUNCE 500  // button debouncer

const int pin = 6;
/*
 * Define macro to put error messages in flash memory
 */
#define error(msg) error_P(PSTR(msg))


//////////////////////////////////// SETUP
void setup() {
  pinMode(pin, INPUT);
  Serial.begin(9600);           // set up Serial library at 9600 bps for debugging
  
  putstring_nl("\nWave test!");  // say we woke up!
  
  putstring("Free RAM: ");       // This can help with debugging, running out of RAM is bad
  Serial.println(FreeRam());

  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    error("Card init. failed!");  // Something went wrong, lets print out why
  }
  
  // enable optimize read - some cards may timeout. Disable if you're having problems
  card.partialBlockRead(true);
  
  // Now we will look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {   // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                           // we found one, lets bail
  }
  if (part == 5) {                     // if we ended up not finding one  :(
    error("No valid FAT partition!");  // Something went wrong, lets print out why
  }
  
  // Lets tell the user about what we found
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(), DEC);     // FAT16 or FAT32?
  
  // Try to open the root directory
  if (!root.openRoot(vol)) {
    error("Can't open root dir!");      // Something went wrong,
  }
  
  // Whew! We got past the tough parts.
  putstring_nl("Files found (* = fragmented):");

  // Print out all of the files in all the directories.
  root.ls(LS_R | LS_FLAG_FRAGMENTED);
}

//////////////////////////////////// LOOP
void loop() {
  if (boxIsOpen()) 
  {
    playcomplete("RICKROLL.WAV");
  }
}

/////////////////////////////////// HELPERS
/*
 * print error message and halt
 */
void error_P(const char *str) {
  PgmPrint("Error: ");
  SerialPrint_P(str);
  sdErrorCheck();
  while(1);
}
/*
 * print error message and halt if SD I/O error, great for debugging!
 */
void sdErrorCheck(void) {
  if (!card.errorCode()) return;
  PgmPrint("\r\nSD I/O error: ");
  Serial.print(card.errorCode(), HEX);
  PgmPrint(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}
/*
 * check if the box is open, meaning the pin is HIGH, and we should cue Mr Astley
 */
bool boxIsOpen()
{
  static byte previous;
  static long time;
  byte reading;
 
  reading = digitalRead(pin);
  if (reading == LOW && previous == HIGH && millis() - time > DEBOUNCE)
  {
    // box is open
    time = millis();
    previous = reading;
    return true;
  }
  previous = reading;
  return false;
}

// Plays a full file from beginning to end with no pause.
void playcomplete(char *name) {
  playfile(name);
  while (wave.isplaying) {
  // do nothing while it's playing
  }
  // now it's done playing
}
 
void playfile(char *name) {
  // see if the wave object is currently doing something
  if (wave.isplaying) {// already playing something, so stop it!
    wave.stop(); // stop it
  }
  // look in the root directory and open the file
  if (!file.open(root, name)) {
    putstring("Couldn't open file "); Serial.print(name); return;
  }
  // OK read the file and turn it into a wave object
  if (!wave.create(file)) {
    putstring_nl("Not a valid WAV"); return;
  }
  
  // ok time to play! start playback
  wave.play();
}
