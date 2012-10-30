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
const int top = 58;
const int center = 73;
const int bottom = 88;
volatile int state = LOW;

void setup()
{
  Serial.begin(9600);
  robot.attach(9);
  robot.write(0);
  lastTime = millis();
  attachInterrupt(0, react, RISING);
}

void loop()
{
  robot.write(0);
  if (state == HIGH)
  {
    emote();
    state = LOW;
  }
  if (millis() - lastTime > quietPeriod)
  {
    i = random(1, 4);
    if (i == 1) {
      fidget();
    } else {
      twitch();
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
    Serial.print("To: ");
    Serial.println(positions[i]);
    
    robot.write(positions[i]);
    
    Serial.print("Waiting: ");
    Serial.println(positions[i+1]);
    
    delay(positions[i+1]);
  }
  resetQuietPeriod();
}

void react()
{
  state = HIGH;
}

void emote()
{
  for (i = 1000; i < 4000; i += 100)
  {
    tone(8, i, 100);
    delay(10);
  }
  const int num = 12;
  int positions[num] = {top, quick, 
     center, quick, top, quick, 
     center, quick, top, quick, 
     center, slow * 2};
  move(positions, num);
}

void fidget()
{
  const int num = 14;
  int positions[num] = {
    bottom, quick, top, medium, 
    center, quick, top, quick, 
    center, quick, top, quick,
    bottom, slow};
  move(positions, num);
}

void twitch()
{
  int positions[4] = {bottom, quick, center, medium};
  move(positions, 4);
}
