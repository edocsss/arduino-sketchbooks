//Libraries
#include <DHT.h>
#include <LiquidCrystal.h>

//Define the DHT11 properties
#define DHTPIN 12
#define DHTTYPE DHT11

//Define the LCD Backlight Pin and LDR Pin
#define BL_PIN 10
#define LDR_PIN 2

//Define the return value for particular buttons
#define RIGHT 0
#define LEFT 1

//Creating objects
DHT tempSensor(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//Variable declaration
float tempC, humidity;
int LDRValue, keypad;

int currentSlide = 0, nextSlide = 0;
unsigned long time;

void setup () {
  //Initialization
  Serial.begin(9600);
  lcd.begin(16, 2);
  tempSensor.begin();
  pinMode(BL_PIN, OUTPUT);
  
  //First sensor reading
  tempC = tempSensor.readTemperature();
  humidity = tempSensor.readHumidity();
  LDRValue = analogRead(LDR_PIN);
  
  //Print to LCD for the first time
  printLCD();
  
  //Initiating timer
  time = millis();
}

void loop () {
  //Continuous LDR and DHT11 reading
  tempC = tempSensor.readTemperature();
  humidity = tempSensor.readHumidity();
  LDRValue = analogRead(LDR_PIN);
  analogWrite(BL_PIN, map(LDRValue, 0, 1023, 50, 200));
  
  //Check for which keypad is pressed
  keypad = readKeypad();
  
  //Check what to be written next
  nextScreen(keypad);
  
  //Re-print the LCD IFF it has been 2 minutes or there is a button pressed
  if (millis() - time >= 2000 || nextSlide != currentSlide) {
    printLCD();
    time = millis();
  }
}

//Check which keypad is pressed
int readKeypad () {
  int keyReading = analogRead(0);
  
  if (keyReading < 50) return RIGHT;
  if (keyReading >= 450 && keyReading < 650) return LEFT;
  
  return -1;
}

//Update which to write on the LCD next
void nextScreen (int keyPad) {
  switch (currentSlide) {
    case 0 :
      if (keyPad == RIGHT) nextSlide = 1;
      break;
    
    case 1 :
      if (keyPad == LEFT) nextSlide = 0;
      break;
    
    default :
      nextSlide = -1;
      break;
  }
}

//Print on the LCD!!
void printLCD () {
  lcd.clear();
  switch (nextSlide) {
    case 0 :
      lcd.setCursor(0, 0);
      lcd.print("Temp.: ");
      lcd.print(tempC);
      lcd.print(" C");
      
      lcd.setCursor(0, 1);
      lcd.print("LDR Value: ");
      lcd.print(LDRValue);
      break;
    
    case 1 :
      lcd.setCursor(0, 0);
      lcd.print("Humidity: ");
      lcd.print(humidity);
      lcd.print("%");
    
      lcd.setCursor(0, 1);
      lcd.print("LDR Value: ");
      lcd.print(LDRValue);
      break;
      
    default :
      lcd.setCursor(0, 0);
      lcd.print("Invalid slide no.!");
      break;
  }
  
  //Update the current slide
  currentSlide = nextSlide;
}
