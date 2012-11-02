#include <Servo.h>
#define QUIET 0
#define TWITCHINGR 1
#define TWITCHINGL 2
#define FIDGETING 3
#define EMOTING 4

volatile int state = QUIET;
Servo robot;
unsigned long lastTime = 0;
int interval;
int i = 0;

//durations
const int quick = 100;
const int medium = 500;
const int slow = 1000;
//positions
int center = 90;
int range = 5;
int top = center + range;
int bottom = center - range;

int emotePositions[16] = {
   top, quick, center, quick, 
   top, quick, center, quick, 
   bottom, quick, center, quick,
   bottom, quick,
   center, slow};
int fidgetPositions[16] = {
  bottom, quick, top, medium, 
  center, quick, top, quick, 
  center, quick, top, quick,
  bottom, slow, center, slow};
int twitchLpositions[4] = {bottom, quick, center, medium};
int twitchRpositions[4] = {top, quick, center, medium};

void setup()
{
  robot.attach(9);
  attachInterrupt(0, react, RISING);
  
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - lastTime > interval) 
  {
    lastTime = currentMillis;
    doState();
  }
}

void doState()
{
  Serial.println(state);
  
  switch(state)
  {
    case QUIET:
      randomBehavior();
      break;
    case TWITCHINGR:
      twitchRight();
      break;
    case TWITCHINGL:
      twitchLeft();
      break;
    case FIDGETING:
      fidget();
      break;
    case EMOTING:
      emote();
      break;
    default:
      goQuiet();
  }
}

void react()
{
  state = EMOTING;
}

void bweep()
{
  for (i = 1000; i < 4000; i += 100)
  {
    tone(8, i, 100);
    delay(10);
  }
}

void randomBehavior()
{
  state = random(1, 3);
}

void twitchLeft()
{
  if (i > 3)
  {
    goQuiet();
    return;
  }
  move(twitchLpositions);
}

void twitchRight()
{
  if (i > 3)
  {
    goQuiet();
    return;
  }
  move(twitchRpositions);
}

void fidget()
{
  if (i > 16)
  {
    goQuiet();
    return;
  }
  move(fidgetPositions);
}

void emote()
{
  if (i > 16)
  {
    goQuiet();
    return;
  }
  if (i == 0)
  {
    bweep();
  }
  move(emotePositions);
}

void goQuiet()
{
  i = 0;
  state = QUIET;
  interval = random(5, 25) * 100;
}

void move(int positions[])
{
  Serial.print("To: ");
  Serial.println(positions[i]);
  Serial.print("Interval: ");
  Serial.println(positions[i+1]);

  robot.write(positions[i]);
  delay(10);
  interval = positions[i+1];
  i += 2;
}

