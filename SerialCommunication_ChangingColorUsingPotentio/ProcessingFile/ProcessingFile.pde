import processing.serial.*;

Serial arduinoPort; //A Serial object to connect with the Arduino
String portName; //Contain the name of the Arduino COM port
int incomingByte; //Store the incoming byte via the Serial line
int fillColor = 0; //Define the fill color of the ellipse -> based on the potentiometer value
boolean init = false; //Tell whether it is the first communication between Processing and the Arduino

void setup () {
  //Setting up the canvas 400 x 400
  size(400, 400);
  
  //Getting the COM port name
  portName = Serial.list()[0];
  
  //Creating an instance of the Serial class object
  arduinoPort = new Serial(this, portName, 9600);
}

void draw () {
  //Fill in the ellipse with the fillColor
  fill(fillColor);
  
  //Create an ellipse in the middle of the canvas with the defined fill color
  ellipse(width / 2, height / 2, 200, 200);
}

//This function is initiated whenever there is something in the Serial line (e.g. incoming data)
void serialEvent (Serial arduinoPort) {
  //Read one byte from the Serial line
  incomingByte = arduinoPort.read();
  
  if (init) {
    //Set the fillColor with the potentio value
    fillColor = incomingByte;
    
    //Give signal to the board to send another potentiometer reading to Processing
    arduinoPort.write('z');
  } 
  
  //If it is the first communication between Processing and the board
  else {
    //Check the "Hello" sign (which is 'z')
    if (incomingByte == 'z') {
      //Clear the buffer to prevent wrong reading after this -> sayHello is a loop -> this might cause the Serial buffer to contain a lot of 'z' -> need to be cleared
      arduinoPort.clear();
      
      //Change init to give signal that the next reading is not the "Hello" sign
      init = true;
      
      //Say "Hello" back to the Arduino -> stop the sayHello() loop
      arduinoPort.write('z');
    }
  }
}
