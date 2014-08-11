import processing.serial.*;

//Constant declaration
final int potentioNumber = 3;

//Serial line variable
Serial arduinoPort;
String portName;

//Data receiver variable
boolean init = false;
int incomingByte;
int[] fillColor = new int[potentioNumber]; //Stores the mapped potentio values
int counter = 0; //Tell fillColor in which index the potentio value should be stored
int R = 0, G = 0, B = 0; //For fill()

void setup () {
  //Initialize canvas
  size(500,500);
  
  //Creating a Serial objet
  portName = Serial.list()[0];
  arduinoPort = new Serial(this, portName, 9600);
}

void draw () {
  fill(R, G, B);
  ellipse(width / 2, height / 2, 200, 200);
}

void serialEvent (Serial arduinoPort) {
  //Store one incoming byte
  incomingByte = arduinoPort.read();
 
  if (init) {
    fillColor[counter] = incomingByte; //Don't use fillColor[counter] = arduinoPort.read() -> double read of value -> possibility of having an empty Serial line but we want to read it -> -1
    counter++; //Increment the index for next incoming byte
    
    //When 3 bytes have been stored in the array, move it to R, G, B and reset the counter
    if (counter >= potentioNumber) {
      R = fillColor[0];
      G = fillColor[1];
      B = fillColor[2];
      counter = 0;
      arduinoPort.write('z');
    }
  } 
  
  else {
    //Check the first 'z' from Arduino
    if (incomingByte == 'z') {
      arduinoPort.clear();
      init = true;
      arduinoPort.write('z');
    }
  }
}
