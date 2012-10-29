#include <Servo.h>
Servo robot;
long lastTime;
int quietPeriod = 500;
int i = 0;
const int s = 100;
const int m = 500;
const int g = 1000;

volatile int state = LOW;

void setup()
{
  robot.attach(9);
  robot.write(0);
  lastTime = 0;
  attachInterrupt(0, react, RISING);
}

void loop()
{
  robot.write(0);
  if (state == HIGH)
  {
    emote();
    state = LOW;
    delay(2*g);
    resetQuietPeriod();
  }
  if (millis() - lastTime > quietPeriod)
  {
    fidget();
    resetQuietPeriod();
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
}

void react()
{
  state = HIGH;
}

void emote()
{
  const int num = 12;
  int positions[num] = {160, s, 
     80, s, 160, s, 
     80, s, 160, s, 
     80, g * 2};
  move(positions, num);
}

void fidget()
{
  const int num = 14;
  int positions[num] = {
    30, s, 120, m, 
    90, s, 120, s, 
    90, s, 120, s,
    50, g};
  move(positions, num);
}
