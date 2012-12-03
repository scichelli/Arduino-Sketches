char rfidIn = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    rfidIn = Serial.read();
    Serial.write(rfidIn);
  }
}
