//Variable declaration
int vxPin = 0;
int vx;
int vyPin = 1;
int vy;
int incomingByte;

void setup () {
  //Serial initialization
  Serial.begin(9600);
  sayHello();
}

void loop () {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    
    //Map the potentios' value -> range 0-255 since Serial.write() sends a value of maximum only 1 byte!
    //If we send a value more than 255, it will send the wrong value!
    vx = map(analogRead(vxPin), 0, 1023, 0, 255);
    vy = map(analogRead(vyPin), 0, 1023, 0, 255);
    
    //Send the data
    Serial.write(vx);
    Serial.write(vy);
  }
}

void sayHello() {
  while (Serial.available() <= 0) {
    Serial.write('z');
    delay(20);
  }
}
