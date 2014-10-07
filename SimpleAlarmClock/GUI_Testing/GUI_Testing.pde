import controlP5.*;

ControlP5 c;

void setup () 
{
  
  c = new ControlP5(this);
  size(200, 200);
  
  textSize(16);
  fill(0);
  text("Clock: ", 20, 40);
  
  int h = hour(), m = minute(), s = second();
  text(h, 75, 40);
  text(":" + m + ":" + s, 95, 40);
  
  c.addButton("button1").setPosition(20, 50);
}

void draw () 
{
}
