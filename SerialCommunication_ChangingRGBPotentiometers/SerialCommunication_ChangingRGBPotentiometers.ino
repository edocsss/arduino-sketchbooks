#define POTENTIONUMBER 3

int potentioPins[POTENTIONUMBER] = {0, 1, 2}; //Array containing the pin numbers
int potentioValues[POTENTIONUMBER]; //Array containing the mapped read value of the potentiometer
int val; //Store the raw reading from the potentiometer -> before mapped
int incomingByte; 

void setup () {
  Serial.begin(9600);
  sayHello();
}

void loop () {
  //Check whether Processing has done its job -> check whether it sends a 'z'
  if (Serial.available() > 0) {
    //Receiving the 'z' sent by Processing
    incomingByte = Serial.read();
    
    //Loops for getting the analog value for each potentio
    for (int i = 0; i < POTENTIONUMBER; i++) {
      //Store raw value
      val = analogRead(potentioPins[i]);
      
      //Store mapped value
      potentioValues[i] = map(val, 0, 1023, 0, 255);
      
      //Sending the value of a particular potentiometer
      Serial.write(potentioValues[i]);
    }
  }
}

//Initialize the communication between the Arduino and Processing
void sayHello () {
  while (Serial.available() <= 0) {
    Serial.write('z');
  }
}
