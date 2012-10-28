#include <Servo.h>
Servo robot;
long lastTime;
int quietPeriod = 500;

void setup()
{
  robot.attach(9);
  robot.write(0);
  lastTime = 0;
}

void loop()
{
  robot.write(0);
  if (millis() - lastTime > quietPeriod)
  {
    fidget();
    quietPeriod = random(5, 25) * 100;
    lastTime = millis();
  }
}

void fidget()
{
  robot.write(30);
  delay(100);
  robot.write(120);
  delay(500);
  robot.write(90);
  delay(100);
  robot.write(120);
  delay(100);
  robot.write(90);
  delay(100);
  robot.write(120);
  delay(100);
  robot.write(50);
  delay(1000);
}
