const int ledNumber = 5;

int potentioPin = 0;
int potentioValue;

int ledPins[ledNumber] = {2, 3, 4, 5, 6};
int ledStates[ledNumber] = {HIGH, LOW, LOW, LOW, LOW};
int i;

void setup () {
  //Setting the pinMode for each LED
  for (i = 0; i < ledNumber; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop () {
  potentioValue = analogRead(potentioPin);
  potentioValue = map(potentioValue, 0, 1023, 0, 5);
  
  ledStateUpdate();
  ledUpdate();
}    

void ledStateUpdate () {
  //Clearing all LED's state
  for (i = 0; i < ledNumber; i++) {
    ledStates[i] = LOW;
  }
  
  //Calibrating the potentiometer
  if (potentioValue > 4) {
    potentioValue = 4;
  }
  
  //Turning on the particular LED based on potentioValue
  ledStates[potentioValue] = HIGH;
}

void ledUpdate () {
  for (i = 0; i < ledNumber; i++) {
    digitalWrite(ledPins[i], ledStates[i]);
  }
}
