#define LED 13
bool speedingUp;
int delayDuration;

void setup()
{
  pinMode(LED, OUTPUT);
  speedingUp = true;
  delayDuration = 1;
}

void loop()
{
  updateDelayDuration();
  blinkOn(delayDuration);
  blinkOff(delayDuration);
  updateDirection();
}

void updateDelayDuration()
{
  if (speedingUp)
  {
    delayDuration++;
  }
  else
  {
    delayDuration--;
  }
}

void updateDirection()
{
  if (delayDuration > 100 || delayDuration < 1)
  {
    speedingUp = !speedingUp;
  }
}

void blinkOn(int duration)
{
  digitalWrite(LED, HIGH);
  delay(duration);
}

void blinkOff(int duration)
{
  digitalWrite(LED, LOW);
  delay(duration);
}
