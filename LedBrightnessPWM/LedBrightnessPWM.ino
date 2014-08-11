int ledPin = 6; //Need to use a PWM Pin!
int brightness = 0;
int increment = 5;

void setup () {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop () {
  analogWrite(ledPin, brightness);
  brightness += increment;
  
  Serial.println(brightness);
  Serial.println(increment);
  
  if (brightness == 0 || brightness == 255) {
    increment = -increment;
  }
  
  delay(50);
}
