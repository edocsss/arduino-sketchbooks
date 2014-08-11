const int switchPin = 2;
const int ledPin = 4;
byte ledState = LOW:

int currentState;
int lastState = LOW; //Real time change of the currentState
int lastDebounceState = LOW; //The real last switch state after debouncing

unsigned long timer;
unsigned int debounceDelay = 50;

void setup () {
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop () {
  curentState = digitalRead(switchPin);
  
  //Check only when the button is pressed -> change from LOW to HIGH ONLY!!
  if (currentState != lastState && currentState) {
    //Start the timer
    timer = millis();
  }
  
  //Check only if the button has been pressed > debounceDelay
  if (millis() - timer > debounceDelay) {
    //Check the current state and the lastDebounceState
    if (currentState != lastDebounceState) {
      //Update the lastDebounceState as the button has been pressed > debounceDelay -> debounced!!
      lastDebounceState = currentState;
      
      //Change the LED state IFF the button is pressed -> change from LOW to HIGH!!
      if (currentState) {
        ledState = !ledState;
      }
    }
  }
  
  digitalWrite(ledPin, ledState);
  lastState = currentState; //Real time update of the current state -> used for comparison in the next loop!!
}
