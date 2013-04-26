#define motor 10
#define walk 7
#define run 8
#define button 2
//Digital Pin 2 is Interrupt 0
int buttonState = 0;

void setup()
{
  pinMode(motor, OUTPUT);
  pinMode(walk, OUTPUT);
  pinMode(run, OUTPUT);
  pinMode(button, INPUT);
  digitalWrite(walk, HIGH);
}

void loop()
{
  buttonState = digitalRead(button);
  if (buttonState)
  {
    digitalWrite(walk, HIGH);
    digitalWrite(run, LOW);
    analogWrite(motor, 0);
  }
  else
  {
    digitalWrite(walk, LOW);
    digitalWrite(run, HIGH);
    analogWrite(motor, 710);
  }
}
