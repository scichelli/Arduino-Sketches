#include <Servo.h>
Servo robot;
long lastTime;
int quietPeriod = 500;

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
    delay(2000);
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

void react()
{
  state = HIGH;
}

void emote()
{
  robot.write(160);
  delay(100);
  robot.write(80);
  delay(100);
  robot.write(160);
  delay(100);
  robot.write(80);
  delay(100);
  robot.write(160);
  delay(100);
  robot.write(80);
  delay(2000);
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
