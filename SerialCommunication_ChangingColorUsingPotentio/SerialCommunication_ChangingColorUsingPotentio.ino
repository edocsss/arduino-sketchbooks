int potentioPin = 0;
int potentioValue = 0;
char incomingByte;

void setup () {
  //Serial communication initialization
  Serial.begin(9600);
  
  //Keep sending 'z' until the processing gives respond
  sayHello();
}

void loop () {
  if (Serial.available() > 0) {
    //The reading is actually only to take the byte out of the buffer -> only 1 byte
    incomingByte = Serial.read();
    
    //Reading the analog value of potentiometer
    potentioValue = analogRead(potentioPin);
    
    //Mapping the value
    potentioValue = map(potentioValue, 0, 1023, 0, 255);
    
    //Sending the value
    Serial.write(potentioValue);
  }
}

void sayHello () {
  while (Serial.available() <= 0) {
    Serial.write('z');
    delay(200);
  }
}
