const int ledPin = ;
const int switchPin = ;
int switchState;

void setup () {
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin, INPUT);
  switchState = 0;
}

void loop () {
  switchState = digitalRead(switchPin);
  delay(20);
  
  if (switchState) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
