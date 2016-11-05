#include <DHT.h>
#include <EEPROM.h>

#define DHTPIN 12
#define DHTTYPE DHT11
DHT tempSensor(DHTPIN, DHTTYPE);

byte eepromIndex = 0;
float tempC, humidity, averageTemp, averageHumid;
float totalTempF = 0.0, totalHumidF = 0.0;
unsigned int counter = 0;
unsigned long timer = millis();

void setup () {
  tempSensor.begin();
}

void loop () {
  tempC = tempSensor.readTemperature();
  humidity = tempSensor.readHumidity();
  
  totalTempF += tempC;
  totalHumidF += humidity;
  counter++;
  
  if (millis() - timer >= 86400000) {
    // Save the data after 1 day
    averageTemp = totalTempF / counter;
    averageHumid = totalHumidF / counter;
    
    // Format -> DAY, MONTH, AVERAGE TEMP, AVERAGE HUMID
    // Average temp -> when reading, (x + 200) / 10
    // Average humid -> when reading, (x + 600) / 10
    // where x is temp or humid
    // EEPROM can hold 1024 bytes -> 1024 / 4 = 256 days
    EEPROM.write(eepromIndex++, day());
    EEPROM.write(eepromIndex++, month());
    EEPROM.write(eepromIndex++, (int) ((averageTemp * 10) - 200));
    EEPROM.write(eepromIndex++, (int) ((averageHumid * 10) - 600));
    
    totalTempF = totalHumidF = 0.0;
    counter = 0;
    
    if (eepromIndex == 120) blinkLED();
  }
  
  delay(5000);
}

void blinkLed () {
  while (true) {
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
  }
}
