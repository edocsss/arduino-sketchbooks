int ledPin = 6;
int potentioPin = 0;
unsigned int potentioValue;

void setup () {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop () {
  potentioValue = analogRead(potentioPin);
  potentioValue = map(potentioValue, 0, 1023, 0, 255);
  delay(10);
  
  Serial.print("Potentiometer: ");
  Serial.println(potentioValue);
  
  analogWrite(ledPin, potentioValue);
  delay(20);
}
  
