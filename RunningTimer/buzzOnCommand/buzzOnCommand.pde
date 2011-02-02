#define MOTOR 3

void setup()
{
  pinMode(MOTOR, OUTPUT);
}

void loop()
{
  analogWrite(MOTOR, 710);
  delay(500);
  analogWrite(MOTOR, 0);
  delay(1000);
}