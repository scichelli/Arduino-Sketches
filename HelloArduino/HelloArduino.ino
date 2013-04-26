#define led 13
#define button 2
int buttonState = 0;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);
}

void loop()
{
  buttonState = digitalRead(button);
  digitalWrite(led, 1 - buttonState);
}
