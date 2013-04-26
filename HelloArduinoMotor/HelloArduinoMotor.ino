#include <Servo.h>

Servo robot;
int center = 70;
int left = center - 10;
int right = center + 10;

void setup()
{
  robot.attach(9);
}

void loop()
{
  robot.write(center);
  delay(500);
  robot.write(left);
  delay(500);
  robot.write(center);
  delay(500);
  robot.write(right);
  delay(500);
}
