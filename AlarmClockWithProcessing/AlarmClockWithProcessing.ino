#include <LiquidCrystal.h>

#define BL_PIN 10
//#define BUZZER 11
#define LED_PIN 2

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
unsigned long timer;
byte time[3], count = 0;
byte incomingByte, dummyByte;
boolean initialize = false;

void setup () {
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("00 : 00 : 00");
  //pinMode(BUZZER, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  timer = millis();
  
  sayHello();
}

void loop () {
  if (Serial.available() > 0) {
    //First time getting a data from Processing -> give signal 'n' to let Processing send the next data
    if (!initialize) {
      //Dummy reading the signal -> useless -> only to tell arduino to read data, but not to use that character signal
      dummyByte = Serial.read();
      Serial.write('n');
      initialize = true;
    }
    
    //Read one byte from the buffer
    incomingByte = Serial.read();
    
    //Read the time data only if it is not the 'n' signal or a white space (ASCII 255)!!
    if (incomingByte != 'n' && incomingByte != 255) {
      //Store the data
      time[count] = incomingByte;
      count++;
      
      //Reset the counter
      if (count >= 3) {
        count = 0;
      
        //Tell Processing to send the next data
        Serial.write('n');
      }
    }
  }
  
  //Rewrite the LCD screen only after one second
  if (millis() - timer >= 500) {
    //Setting up
    lcd.setCursor(0, 0);
    lcd.clear();
    
    //Write the time -> HOUR : MINUTE : SECOND
    lcd.print(time[0]);
    lcd.print(" : ");
    lcd.print(time[1]);
    lcd.print(" : ");
    lcd.print(time[2]);
    
    //Reset the timer
    timer = millis();
  }
}

//First communication trial
void sayHello () {
  while (Serial.available() <= 0) {
    Serial.write('b');
    delay(100);
  }
}


