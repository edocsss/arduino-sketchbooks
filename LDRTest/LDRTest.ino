int ldrPin = 1;
int ldrValue;

int ledPin = 3;
int ledValue;

void setup () {
  Serial.begin(9600);
}

void loop () {
  ldrValue = analogRead(ldrPin);
  ledValue = map(ldrValue, 0, 1023, 255, 0); //Dark = brighter
  
  Serial.print(ldrValue);
  Serial.print("  ");
  Serial.println(ledValue);
  
  //Write the PWM value
  analogWrite(ledPin, ledValue);
  delay(10);
}
