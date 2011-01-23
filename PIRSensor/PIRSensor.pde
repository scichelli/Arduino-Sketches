int ledPin = 13;
int PIRSensor = 1;
int state = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(PIRSensor, INPUT);
  Serial.begin(9600);
}

void loop(){
  state = digitalRead(PIRSensor);
  
  if (state != 0)
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("detected");
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }
   delay(100);
}