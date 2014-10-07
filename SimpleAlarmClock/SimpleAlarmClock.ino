#include <LiquidCrystal.h>

#define BUZZER 3
#define SWITCH 2
#define BL_PIN 10

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int LDRValue;
char incomingByte;

long timer;
int h, m;

void setup () {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Alarm Clock!");
  
  Serial.begin(9600);
  pinMode(BUZZER, OUTPUT);
  pinMode(SWITCH, INPUT); 
  pinMode(BL_PIN, OUTPUT);
  analogWrite(BL_PIN, 100);
  
  sayHello();
}

void loop () {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    
    if (incomingByte == 'y') {
      //y means ring the alarm
      alarm();
      
      //After the button is pushed -> stop alarm and tell the computer
      Serial.write('n');
      Serial.flush();
      
    } else if (incomingByte == 'h') {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Alarm: ");
      
      //Read hour
      h = Serial.read();
      
      //Add a zero if h < 10
      if (h < 10) {
        lcd.print('0');
      }
      
      //Print the hour
      lcd.print(h);
      lcd.print(":");
      
    } else if (incomingByte == 'm') {
      lcd.setCursor(0, 11);
      
      //Read the minute
      m = Serial.read();
      
      if (m < 10) {
        lcd.print("0");
      }
      
      //Print the minute
      lcd.print(m);
    }
  }
  
  delay(50);
}

//First serial comm with Processing
void sayHello () {
  while (Serial.available() <= 0) {
    Serial.write('z');
    delay(100);
  }
}

void alarm() {
  boolean buttonPushed = false;
  int currentState, lastKnownState = LOW;
  
  unsigned long switchTimer, toneTimer = millis();
  int debounceDelay = 50;
  
  while (!buttonPushed) {
    //Ring the bell for every 500ms
    if (millis() - toneTimer >= 500) {
      //Play C5 note for 500ms
      tone(BUZZER, 523, 500);
      
      //Stop after 500ms
      noTone(BUZZER);
      
      //Reset the timer
      toneTimer = millis();
    }
    
    //Read current switch state
    currentState = digitalRead(SWITCH);
    
    //Reset timer only if the button is pressed
    if (currentState != lastKnownState && currentState == HIGH) {
      timer = millis();
    }
    
    //Check whether the button has been pushed for > debounceDelay
    if (millis() - timer > debounceDelay && currentState == HIGH) {
      buttonPushed = true;
    }
    
    //Updating status
    lastKnownState = currentState; 
  }
}
