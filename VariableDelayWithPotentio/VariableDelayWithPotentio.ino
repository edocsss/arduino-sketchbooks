int potentioPin = 0;
unsigned int potentioValue;
int ledPin = 7;

void setup () {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop () {
  potentioValue = analogRead(potentioPin);
  Serial.print("Potentiometer: ");
  Serial.println(potentioValue);
  delay(20);
  
  digitalWrite(ledPin, HIGH);
  delay(potentioValue);
  digitalWrite(ledPin, LOW);
  delay(potentioValue);
}
