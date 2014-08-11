const int commonIO = 0;
const int deviceNumber = 2;
int pinA = 4, pinB = 3, pinC = 2;
int selector;
int analogValue;

void setup () {
  Serial.begin(9600);
  
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
}

void loop () {
  for (selector = 0; selector < deviceNumber; selector++) {
    digitalWrite(pinA, bitRead(selector, 0));
    digitalWrite(pinB, bitRead(selector, 1));
    digitalWrite(pinC, bitRead(selector, 2));
    
    analogValue = analogRead(commonIO); 
    
    Serial.print(selector);
    Serial.print("  ");
    Serial.println(analogValue);
  }
  
  delay(1000);
}
