#define LED 13

void setup()
{
  pinMode(LED, OUTPUT);
}

void loop()
{
  beat();
  beat();
  rest();
  beat();
  beat();
  beat();
  rest();
}

void beat()
{
  blinkOn(200);
  blinkOff(200);
}

void rest()
{
  delay(600);
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
