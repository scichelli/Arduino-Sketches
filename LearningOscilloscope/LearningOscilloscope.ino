void setup()
{
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  digitalWrite(11, HIGH);
  delayMicroseconds(1000);
  digitalWrite(13, LOW);
  digitalWrite(11, LOW);
  delayMicroseconds(1000);
}
