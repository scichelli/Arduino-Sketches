#define MOTOR 3
#define LED 13

void setup()
{
  pinMode(MOTOR, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  analogWrite(MOTOR, 710);
  digitalWrite(LED, HIGH);
  delay(500);
  analogWrite(MOTOR, 0);
  digitalWrite(LED, LOW);
  delay(1000);
}
