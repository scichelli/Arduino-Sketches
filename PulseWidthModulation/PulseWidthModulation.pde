#define LED 9
#define BUTTON 7

int buttonVal = 0;
int oldButtonVal = 0;
int ledState = 0;
int brightness = 128;
unsigned long startTime = 0;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop()
{
  buttonVal = digitalRead(BUTTON);
  if (buttonVal == HIGH && oldButtonVal == LOW)
  {
    ledState = 1 - ledState;
    startTime = millis();
    delay(10);
  }
  
  if (buttonVal == HIGH && oldButtonVal == HIGH)
  {
    if (ledState == 1 && (millis() - startTime > 500))
    {
      brightness++;
      delay(10);
      if (brightness > 255)
      {
        brightness = 0;
      }
    }
  }
  
  oldButtonVal = buttonVal;
  
  if (ledState == 1)
  {
    analogWrite(LED, brightness);
  }
  else
  {
    analogWrite(LED, 0);
  }
}
