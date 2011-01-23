#define SWITCH 8
int ledPins[] = {2, 3, 4, 5, 6, 7};
const int ledPinsCount = 6;
int redEyePins[] = {10, 11};
const int redEyePinsCount = 2;
long durations[ledPinsCount];
int ledStates[ledPinsCount];
long previousTimes[ledPinsCount];
int i;

void setup()
{
  pinMode(SWITCH, INPUT);
  for (i = 0; i < redEyePinsCount; i++)
  {
    //For each red eye LED:
    pinMode(redEyePins[i], OUTPUT);
  }
  for(i = 0; i < ledPinsCount; i++)
  {
    //For each LED:
    pinMode(ledPins[i], OUTPUT); //define all the LED pins as outputs.
    ledStates[i] = random(1); //randomly set the LEDs to on or off (1 or 0).
    durations[i] = GetRandomDuration(); //define a random duration for each LED to stay in that state.
    previousTimes[i] = 0; //at time of setup, the "last time we changed" is at 0 milliseconds, the start of time.
  }
}

void loop()
{
  if (digitalRead(SWITCH) == HIGH)
  {
    TurnOffLeds();
    PulseRedEyes();
  }
  else
  {
    for(i = 0; i < redEyePinsCount; i++)
    {
      //Turn the red eyes all the way off.
      digitalWrite(redEyePins[i], LOW);
    }
    
    for(i = 0; i < ledPinsCount; i++)
    {
      //For each LED:
      if (millis() - previousTimes[i] > durations[i])
      {
        ChangeLed(i); //If this one's duration is up, then flip it.
      }
    }
  }
}

void TurnOffLeds()
{
  for(i = 0; i < ledPinsCount; i++)
  {
    digitalWrite(ledPins[i], LOW);
  }
}

void PulseRedEyes()
{
  //Fade on, then off.
  int j;
  for(j = 0; j < 255; j+=5)
  {
    for(i = 0; i < redEyePinsCount; i++)
    {
      analogWrite(redEyePins[i], j);
      delay(10);
    }
  }
  for(j = 255; j > 0; j-=5)
  {
    for(i = 0; i < redEyePinsCount; i++)
    {
      analogWrite(redEyePins[i], j);
      delay(10);
    }
  }
}

void ChangeLed(int ledPin)
{
  previousTimes[ledPin] = millis(); //update the "last time we changed" to now.
  durations[ledPin] = GetRandomDuration(); //give it a new random duration.
  ledStates[ledPin] = 1 - ledStates[ledPin]; //flip the state between on and off.
  digitalWrite(ledPins[ledPin], ledStates[ledPin]); //set the LED to that state.
}

long GetRandomDuration()
{
  //random number between 1 and 10, then multiplied by 400 to give it a detectable duration.
  return random(1, 10) * 400;
}