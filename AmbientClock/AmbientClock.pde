#define HOUREVEN 12
#define HOURODD 8
#define ledPinsLength 5
int ledPins[] = {
  3, 5, 6, 9, 10};
const long interval = 6000; //make the interval more than 2550;
/* otherwise you'll still be fading when it
 is time to check for the interval again. */
long previousMillis = 0;
int i = 0;
int brightness = 0;
int sixthsOfTime = 0;
int oddHour = 0;
const int fadeDelay = 10; //larger numbers fade slower.

void setup() {
  pinMode(HOUREVEN, OUTPUT);
  pinMode(HOURODD, OUTPUT);
  for(i = 0; i < ledPinsLength; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  SwitchTheHours();
}

void loop() {
  if (sixthsOfTime >= ledPinsLength) {
    RollOverTheHour();
  }

  if (millis() - previousMillis > interval) {
    IndicateElapsedInterval();
  }
}

void RollOverTheHour() {
  previousMillis = millis();
  TurnEverythingOff();
  SwitchTheHours();
  sixthsOfTime = 0;
}

void IndicateElapsedInterval() {
  previousMillis = millis();
  TurnLedOn(sixthsOfTime);
  sixthsOfTime++;
}

void SwitchTheHours() {
  if (oddHour == 0) {
    digitalWrite(HOUREVEN, HIGH);
    digitalWrite(HOURODD, LOW);
  }
  else {
    digitalWrite(HOURODD, HIGH);
    digitalWrite(HOUREVEN, LOW);
  }
  oddHour = 1 - oddHour;
}

void TurnEverythingOff() {
  for(brightness = 255; brightness > 0; brightness -= 1) {
    if (brightness < 5) {
      brightness = 0; //turn them all the way off, instead of leaving a little.
    }
    for(i = 0; i < ledPinsLength; i++) {
      analogWrite(ledPins[i], brightness);
    }
    delay(fadeDelay);
  }
}

void TurnLedOn(int ledPin) {
  for(brightness = 0; brightness < 255; brightness += 1) {
    analogWrite(ledPins[ledPin], brightness);
    delay(fadeDelay);
  }
}