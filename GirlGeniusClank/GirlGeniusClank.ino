#include <Servo.h>
const int QUIET = 0;
const int TWITCHINGR = 1;
const int TWITCHINGL = 2;
const int FIDGETING = 3;
const int EMOTING = 4;

volatile int state = QUIET;
Servo robot;
unsigned long lastTime = 0;
int interval;
int i = 0;

//durations
const int quick = 100;
const int medium = 600;
const int slow = 2000;
//positions
int center = 50;
int range = 15;
int top = center + range;
int bottom = center - range;

int emotePositions[20] = {
   top, quick, center, quick, 
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
  attachInterrupt(0, react, FALLING);
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
  interval = 0;
  i = 0;
}

void bweep()
{
  for (int b = 1000; b < 4000; b += 100)
  {
    tone(8, b, 100);
    delay(10);
  }
}

void randomBehavior()
{
  state = random(1, 4);
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
  if (i > 20)
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
  interval = random(1, 5) * 600;
}

void move(int positions[])
{
  robot.write(positions[i]);
  delay(10);
  interval = positions[i+1];
  i += 2;
}

