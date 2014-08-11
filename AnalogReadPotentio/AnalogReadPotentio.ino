int potentioPin = 0;
unsigned int potentioValue = 0;
float potentioVoltage = 0.0;

void setup () {
  Serial.begin(9600);
}

void loop () {
  potentioValue = analogRead(potentioPin);
  delay(20);
  
  potentioVoltage = potentioValue * (5.0 / 1023.0);
  delay(20);
  
  Serial.println(potentioValue);
  Serial.println(potentioVoltage);
  Serial.println();
  
  delay(100);
}
