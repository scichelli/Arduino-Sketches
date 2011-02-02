int switches[] = {7, 6, 5, 4, 3};
const int switchCount = 5;
int switchStates[switchCount];

int ledPins[] = {8, 9, 10, 11, 12};
const int ledPinCount = 5;
int ledStates[ledPinCount];

int i;

void setup()
{
  for (i = 0; i < ledPinCount; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
  for (i = 0; i < switchCount; i++)
  {
    pinMode(switches[i], INPUT);
    digitalWrite(switches[i], HIGH); // turn on built-in pullup resistor
  }
//  for (i = 0; i < ledPinCount; i++)
//  {
//    showCounter(ledPins[i]);
//  }
  flashAll();
}

void loop()
{
  for (i = 0; i < switchCount; i++)
  {
    switchStates[i] = digitalRead(switches[i]);
    digitalWrite(ledPins[i], switchStates[i]);
  }
}

void showCounter(int led)
{
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}

void flashAll()
{
  for (i = 0; i < ledPinCount; i++)
  {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(500);
  for (i = 0; i < ledPinCount; i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
}