import processing.serial.*;

//Serial related variable
Serial arduinoPort;
String portName;

//Storing data variable
boolean init = false;
int incomingByte;
int counter = 0;
int readVx = 0; //Temporary store the Vx from Arduino
int readVy = 0; //Temporary store the Vy from Arduino

//Color variable
int bgColor = 255;
int fillColor = 0;

//A variable of Ball class
Ball myBall;

void setup () {
  size(800, 500);
  background(bgColor);
  fill(fillColor);
  
  //No outer line
  noStroke();
  
  //Creating an instance of Ball class
  myBall = new Ball();
  
  //Setting up the Serial object
  portName = Serial.list()[0];
  arduinoPort = new Serial(this, portName, 9600);
}

void draw () {
  //Update the position and draw
  myBall.updatePosition();
  myBall.drawBall();
}

void serialEvent (Serial arduinoPort) {
  //Read one byte from the Serial line
  incomingByte = arduinoPort.read();
  
  if (init) {
    //Store the received byte based on the counter state
    switch (counter) {
      case 0 :
        //First byte is for Vx
        readVx = incomingByte;
        
        //Check whether myBall's vx is already negative -> if so, make the read value of vx becomes negative too (the read value is always positive)
        if (myBall.vx < 0) {
          myBall.vx = -readVx;
        } else {
          myBall.vx = readVx;
        }
        
        //Increments counter state
        counter++;
        break;
        
      case 1 :
        //Second byte is for Vy
        readVy = incomingByte;
        
        //Check whether myBall's vy is already negative
        if (myBall.vy < 0) {
          myBall.vy = -readVy;
        } else {
          myBall.vy = readVy;
        }
        
        //Reset the counter as we only need to read 2 bytes
        counter = 0;
        
        //Tell Arduino to send the next reading
        arduinoPort.write('z');
        break;
    }
    
    
  }
  
  else {
    //First communication
    if (incomingByte == 'z') {
      arduinoPort.clear();
      init = true;
      arduinoPort.write('z');
    }
  }
}

//Class declaration
class Ball {
  //Private variable declaration
  private int vx, vy;
  private long begin, end;
  private float x, y, radius;
  private double difference;
  
  //Constructor
  public Ball () {
    this.x = width / 2;
    this.y = height / 2;
    this.radius = 50.0;
    
    this.vx = 0;
    this.vy = 0;
    
    //Timer variable initialization
    this.begin = System.currentTimeMillis();
  }
  
  //Check for wall collision
  public void checkCollision () {
    //X-axis check
    if ((this.x + 0.5 * this.radius >= width) || (this.x - 0.5 * this.radius <= 0)) {
      this.vx = -this.vx;
    }
    
    //Y-axis check
    if ((this.y + 0.5 * this.radius >= height) || (this.y - 0.5 * this.radius <= 0)) {
      this.vy = -this.vy;
    }
  }
  
  //Update the ball's position
  public void updatePosition () {
    //Calculating the time elapsed between updating
    this.end = System.currentTimeMillis();
    this.difference = this.end - this.begin;
    this.begin = this.end;
    
    //Update position
    this.x += this.vx * (this.difference / 1000);
    this.y += this.vy * (this.difference / 1000);
    
    //Check for any wall collision
    this.checkCollision();
  }
  
  //Draw the ball to the canvas
  public void drawBall () {
    
    background(bgColor); //Clear the canvas
    ellipse(this.x, this.y, this.radius, this.radius);
  }
}
