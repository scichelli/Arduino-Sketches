/*
 * When a box (labeled "Cookies!") is opened, play Never Gonna Give You Up
 */
#include <WaveHC.h>
#include <WaveUtil.h>

SdReader card;    // SD memory card
FatVolume vol;    // partition on the card
FatReader root;   // root directory of the volume
FatReader file;   // file to play
WaveHC wave;      // wave (audio) object created from file

#define DEBOUNCE 500  // button debouncer
const int pin = 6;

/*
 * Define macro to put error messages in flash memory
 */
#define error(msg) error_P(PSTR(msg))

void setup() {
  pinMode(pin, INPUT);
  Serial.begin(9600);           // set up Serial library at 9600 bps for debugging
  
  putstring_nl("\nWave test!");
  putstring("Free RAM: ");       // display amount of RAM, to help with debugging
  Serial.println(FreeRam());

  //  if (!card.init(true)) {     // uncomment this line to play with 4 MHz spi if 8MHz is not working
  if (!card.init()) {             // play with 8 MHz spi  
    error("Card initialization failed");  
  }
  
  card.partialBlockRead(true);   // enable optimize read. Some cards may time out; disable if problems.
  
  // search for a FAT partition:
  uint8_t part;
  for (part = 0; part < 5; part++) {   // up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                           // found FAT partition; exit loop
  }
  if (part == 5) {                     // did not find FAT partition -> error
    error("No valid FAT partition");
  }
  
  // Print diagnostics
  putstring("Using partition ");
  Serial.print(part, DEC);
  putstring(", type is FAT");
  Serial.println(vol.fatType(), DEC);    // specifies FAT16 or FAT32
  
  if (!root.openRoot(vol)) {             // open root directory
    error("Can't open root dir!");
  }
  
  putstring_nl("Files found (* = fragmented):");
  root.ls(LS_R | LS_FLAG_FRAGMENTED);   // print out all files found
}

void loop() {
  if (boxIsOpen()) 
  {
    playcomplete("RICKROLL.WAV");
  }
}

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
 * print error message and halt if SD I/O error
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

/*
 * play a full file from beginning to end with no pause
 */
void playcomplete(char *name) {
  playfile(name);
  while (wave.isplaying) {
    // do nothing while it's playing
  }
}

void playfile(char *name) {
  if (wave.isplaying) {
    wave.stop();
  }

  // look in the root directory and open the file
  if (!file.open(root, name)) {
    putstring("Could not open file "); Serial.print(name); return;
  }

  // read the file and turn it into a wave object
  if (!wave.create(file)) {
    putstring_nl("Not a valid WAV"); return;
  }
  
  wave.play();
}
