#include <Servo.h>

int potentioPin = 0;
unsigned int potentioValue;

Servo myServo;
int servoPin = 8;

void setup () {
  myServo.attach(servoPin);
}

void loop () {
  potentioValue = analogRead(potentioPin);
  potentioValue = map(potentioValue, 0, 1023, 0, 180);
  myServo.write(potentioValue);
}
