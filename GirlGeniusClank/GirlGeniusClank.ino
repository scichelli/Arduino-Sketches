#include <Servo.h>

Servo robot;
long lastTime;
int quietPeriod = 500;
int i = 0;
//durations
const int quick = 100;
const int medium = 500;
const int slow = 1000;
//positions
int center = 90;
int top = 90 + 5;
int bottom = 90 - 5;
volatile int state = LOW;

void setup()
{
  robot.attach(9);
  robot.write(center);
  lastTime = millis();
  attachInterrupt(0, react, RISING);
}

void loop()
{
  if (state == HIGH)
  {
    emote();
    state = LOW;
  }
  if (millis() - lastTime > quietPeriod)
  {
    i = random(1, 5);
    if (i == 1) {
      fidget();
    } else if (i == 2 || i == 3) {
      twitchLeft();
    } else {
      twitchRight();
    }
  }
}

void resetQuietPeriod()
{
  quietPeriod = random(9, 25) * 100;
  lastTime = millis();
}

void move(int positions[], int numberOfPositions)
{
  for (i = 0; i < numberOfPositions; i += 2)
  {
    robot.write(positions[i]);
    delay(positions[i+1]);
  }
  resetQuietPeriod();
}

void react()
{
  state = HIGH;
}

void bweep()
{
  for (i = 1000; i < 4000; i += 100)
  {
    tone(8, i, 100);
    delay(10);
  }
}

void emote()
{
  bweep();
  const int num = 16;
  int positions[num] = {
     top, quick, center, quick, 
     top, quick, center, quick, 
     bottom, quick, center, quick,
     bottom, quick,
     center, slow * 2};
  move(positions, num);
}

void fidget()
{
  const int num = 16;
  int positions[num] = {
    bottom, quick, top, medium, 
    center, quick, top, quick, 
    center, quick, top, quick,
    bottom, slow, center, slow};
  move(positions, num);
}

void twitchLeft()
{
  twitch(bottom);
}

void twitchRight()
{
  twitch(top);
}

void twitch(int firstDirection)
{
  int positions[4] = {firstDirection, quick, center, medium};
  move(positions, 4);
}
