import controlP5.*;
import processing.serial.*;
import java.lang.Character;

//GUI
ControlP5 c;

//Arduino related
Serial arduinoPort;
String portName;

//Time related
byte[] time = new byte[] {-1, -1};
byte h, m;
boolean timePrinted = false;
String timeStr;

//Reading data related
boolean init = false;
int incomingByte;

void setup () {
  //Setting up Arduino
  portName = Serial.list()[0];
  arduinoPort = new Serial(this, portName, 9600);
  
  //Debug purpose
  println(portName);
  println(arduinoPort);
  
  //GUI Preparation
  size(400, 200);
  background(0);
  c = new ControlP5(this);
  
  //Adding text
  fill(255);
  textSize(15);
  text("Enter hour: ", 20, 33);
  text("Enter minute: ", 20, 68);
  
  //Adding textboxes
  c.addTextfield("HourField").setPosition(150, 20).setSize(40, 20).setFocus(true);
  c.addTextfield("MinuteField").setPosition(150, 55).setSize(40, 20);
  
  //Write the given alarm clock
  textSize(17);
  text("Alarm Clock: ", 20, 130);
}

public void HourField (String s) 
{
  //Check whether s consists of digits only
  if (allDigits(s) && s.length() < 3 && s.length() > 0)
  {
    //Store to time[0] by converting String to int
    time[0] = toDigits(s);
    
    //Debug message
    println("Hour input is successfully stored!");
    println("Hour: " + time[0]);
  }
  else
  {
    //Not all digits!
    println("Invalid input!");
  }
}

public void MinuteField (String s)
{
  //Check whether s consists of digits only
  if (allDigits(s) && s.length() < 3 && s.length() > 0)
  {
    //Store to time[0] by converting String to int
    time[1] = toDigits(s);
    
    //Debug message
    println("Minute input is successfully stored!");
    println("Minute: " + time[1]);
  }
  else
  {
    //Not all digits!
    println("Invalid input!");
  }
}

public static boolean allDigits(String s)
{
  for (int i = 0; i < s.length(); i++)
  {
    //If there is one character that is not a digit
    if (!Character.isDigit(s.charAt(i))) return false;
  }
  
  return true;
}

public static byte toDigits(String s)
{
  byte result = 0;
  for (int i = 0; i < s.length(); i++)
  {
    result += (byte) Math.pow(10, i) * ((int) s.charAt(s.length() - i - 1) - 48);
  }
  
  return result;
}

/* ---------------------------------------------------------- */

void draw () {
  //Get the time (to get HOUR and MINUTES)
  h = (byte) hour();
  m = (byte) minute();
  
  if (time[0] >= 0 && time[1] >= 0 && !timePrinted) {
    sendTime();
    
    timeStr = "";
    if (time[0] < 10) {
      timeStr += "0" + time[0];
    }
    
    timeStr += ":";
    
    if (time[1] < 10) {
      timeStr += "0" + time[1];
    }
    
    println(timeStr);
    text(timeStr, 150, 130);
    timePrinted = true;
  }
  
  //Ring the bell if it is the targeted time
  if (time[0] == h && time[1] == m && time[0] >= 0 && time[1] >= 0) {
    //arduinoPort.write('y');
    System.out.println("Alarm clock: " + time[0] + " : " + time[1]);
  }
}

//Send time after the hour and minute are acquired
void sendTime() {
  //Sending the hour
  arduinoPort.write('h');
  arduinoPort.write(time[0]);
  
  //Sending the minute
  arduinoPort.write('m');
  arduinoPort.write(time[1]);
}

//Input time via GUI
void inputTime() {
  println("ENTER TIME!!");
  time[0] = -1;
  time[1] = -1;
  timePrinted = false;
}

void serialEvent (Serial arduinoPort) {
  //Read one byte
  incomingByte = arduinoPort.read();
  
  if (init) {
    //If the alarm has been turned off
    if (incomingByte == 'n') {
      inputTime();
    }
  } 
  
  //First hello
  else {
    if (incomingByte == 'z') {
      println(incomingByte);
      arduinoPort.clear();
      init = true;
      arduinoPort.write('z');
      
      //Ask for time
      inputTime();
    }
  }
}
