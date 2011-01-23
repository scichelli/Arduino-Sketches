#define SENSOR 0
#define REDLED 9
#define GREENLED 10
#define BLUELED 11
#define BUTTON 12

int valSensor = 0;
int button = LOW;
int oldButton = LOW;
int state = 0;
char buffer[7];
int pointer = 0;
byte inByte = 0;
byte r = 0;
byte g = 0;
byte b = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT);
}

void loop() {
  valSensor = analogRead(SENSOR);
  Serial.println(valSensor);

  if (Serial.available() > 0) {
    inByte = Serial.read();
    if (inByte == '#') {
      while (pointer < 6) {
        buffer[pointer] = Serial.read();
        pointer++;
      }
      r = hex2dec(buffer[1]) + hex2dec(buffer[0]) * 16;
      g = hex2dec(buffer[3]) + hex2dec(buffer[2]) * 16;
      b = hex2dec(buffer[5]) + hex2dec(buffer[4]) * 16;

      pointer = 0;
    }
  }
  
  button = digitalRead(BUTTON);
  if ((button == HIGH) && (oldButton == LOW)) {
    state = 1 - state;
  }
  oldButton = button;
  
  if (state == 1) {
    analogWrite(REDLED, r);
    analogWrite(GREENLED, g);
    analogWrite(BLUELED, b);
  } else {
    analogWrite(REDLED, 0);
    analogWrite(GREENLED, 0);
    analogWrite(BLUELED, 0);
  }
  
  delay(100);
}

int hex2dec(byte c) {
  if (c >= '0' && c <= '9') {
    return c - '0';
  } else if (c >= 'A' && c <= 'F') {
    return c = 'A' + 10;
  }
}
