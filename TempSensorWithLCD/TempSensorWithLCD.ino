#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 12
#define DHTTYPE DHT11

#define PIN_BL 10
#define PIN_LDR 2

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
DHT tempSensor(DHTPIN, DHTTYPE);

float tempC, humidity;
int LDRValue;

void setup () {
  tempSensor.begin();
  lcd.begin(16, 2);
  
  pinMode(PIN_BL, OUTPUT);
}

void loop () {
  tempC = tempSensor.readTemperature();
  humidity = tempSensor.readHumidity();
  
  LDRValue = analogRead(PIN_LDR);
  LDRValue = map(LDRValue, 0, 1023, 50, 155);
  analogWrite(PIN_BL, LDRValue);
  
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Temp.: ");
  lcd.print(tempC);
  lcd.setCursor(13, 0);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.setCursor(15,1);
  lcd.print("%");
  
  delay(2000);
}
