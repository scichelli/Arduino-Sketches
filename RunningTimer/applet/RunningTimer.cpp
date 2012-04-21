#define MOTOR 3
#define LED 13

#include "WProgram.h"
void setup();
void loop();
void setup()
{
  pinMode(MOTOR, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  analogWrite(MOTOR, 710);
  digitalWrite(LED, HIGH);
  delay(500);
  analogWrite(MOTOR, 0);
  digitalWrite(LED, LOW);
  delay(1000);
}

int main(void)
{
	init();

	setup();
    
	for (;;)
		loop();
        
	return 0;
}

