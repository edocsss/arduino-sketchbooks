//Import libraries
import processing.serial.*;
import java.util.Calendar;
import java.util.Date;
import java.lang.Thread;

//Serial comm related
Serial arduinoPort;
String portName;

//Time related
Calendar calendar;
Date date = new Date();
byte[] time = new byte[3];

//Sending and receivig data related
int incomingByte;
boolean init = false;

void setup () {
  portName = Serial.list()[0];
  arduinoPort = new Serial(this, portName, 9600);
}

void draw () {
  calendar = Calendar.getInstance();
  time[0] = (byte) calendar.get(Calendar.HOUR_OF_DAY);
  time[1] = (byte) calendar.get(Calendar.MINUTE);
  time[2] = (byte) calendar.get(Calendar.SECOND);
}

void serialEvent (Serial arduinoPort) {
  incomingByte = arduinoPort.read();
  
  //Handling serial communication
  if (init) {
    if (incomingByte == 'n') {
      //Send the time array
      for (int i = 0; i < 3; i++) {
        arduinoPort.write(time[i]);
        
        //Pause for a few milliseconds
        try {
          Thread.sleep(50);
        } catch (InterruptedException ex) {
          continue;
        }
      }
      
      arduinoPort.write('n');
    }
  } 
  
  else {
    //Check whether the arduino is ready to begin comm
    if (incomingByte == 'b') {
      arduinoPort.clear();
      init = true;
      arduinoPort.write('b');
    }
  }
}
