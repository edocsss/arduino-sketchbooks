#include <Servo.h>

Servo myServo;
int servoPin = 8;
int currentPos = 0;

void setup () {
  myServo.attach(servoPin);
}

void loop () {
  for (currentPos = 0; currentPos < 180; currentPos++) {
    myServo.write(currentPos);
    delay(20);
  }
  
  for (currentPos = 180; currentPos > 0; currentPos--) {
    myServo.write(currentPos);
    delay(20);
  }
}
