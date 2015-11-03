#define SPEAKER 8
int i = 0;

void setup() {
}

void loop() {
  delay(800);
  
  for (i = 1000; i < 3500; i += 100)
  {
    tone(SPEAKER, i, 100);
    delay(10);
  }
}
