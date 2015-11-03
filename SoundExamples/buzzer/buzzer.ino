#define MOTOR 6
#define FSR 0
int forceReading;
int motorSpeed;

void setup() {
  Serial.begin(9600);
  pinMode(MOTOR, OUTPUT);
  pinMode(FSR, INPUT);
}

void loop() {
  forceReading = analogRead(FSR);
  Serial.print("Analog reading: ");
  Serial.println(forceReading);
  
  motorSpeed = map(forceReading, 800, 1023, 0, 255);
  analogWrite(MOTOR, motorSpeed);
  
  delay(100);
}
