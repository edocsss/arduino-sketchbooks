#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 12
#define DHTTYPE DHT11

#define LDR_PIN 2
#define BL_PIN 10

DHT tempSensor(DHTPIN, DHTTYPE);
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int LDRValue;
float tempC;

void setup () {
  lcd.begin(16, 2);
  tempSensor.begin();
  
  pinMode(BL_PIN, OUTPUT);
} 

void loop () {
  tempC = tempSensor.readTemperature();
  LDRValue = map(analogRead(LDR_PIN), 0, 1023, 80, 200);
  analogWrite(BL_PIN, LDRValue);
  
  //Don't put CLEAR() before tempSensor.readTemperature() as
  //reading temperature needs some time which will cause a little delay
  //reading and writing the temperature
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC);
  lcd.print(" C");
  
  lcd.setCursor(0, 1);
  lcd.print("Mapped LDR: ");
  lcd.print(LDRValue);
  
  delay(1000);
}

