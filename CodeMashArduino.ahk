#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.

#IfWinActive ahk_class SunAwtFrame

::.setup::
(
void setup()
{
	
}
)

::.loop::
(
void loop()
{
	
}
)

::.led::
(
#define led 13
)

::.ledpin::
(
pinMode(led, OUTPUT);
)

::.ledhigh::
(
digitalWrite(led, HIGH);
delay(700);
)

::.ledlow::
(
digitalWrite(led, LOW);
delay(300);
)

; add button to same sketch

::.button::
(
#define button 2
int buttonState = 0;
)

::.buttonpin::
(
pinMode(button, INPUT);
)

::.readbutton::
(
buttonState = digitalRead(button);
)

::.setled::
(
if (buttonState == 1)
{
digitalWrite(led, LOW);
}
else
{
digitalWrite(led, HIGH);
}
)

::.refactor::
(
digitalWrite(led, 1 - buttonState);
)

; motor for new sketch
; setup and loop

::.servo::
(
#include <Servo.h>

Servo robot;
)

::.servosetup::
(
robot.attach(9);
)

::.servoint::
(
int center = 70;
int left = center - 10;
int right = center + 10;
)

::.servoleft::
(
robot.write(center);
delay(500);
robot.write(left);
delay(500);
)

::.servoright::
(
robot.write(center);
delay(500);
robot.write(right);
delay(500);
)