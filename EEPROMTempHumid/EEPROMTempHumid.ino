#include <Time.h>
#include <EEPROMex.h>
#include <EEPROMVar.h>
#include <DHT.h>

#define DHTPIN 12
#define DHTTYPE DHT11
#define LED_PIN 13
#define NO_OF_HOURS 4
#define ONE_HOUR 3600000
#define ONE_MINUTE 6000
#define ONE_SECOND 1000
DHT tempSensor(DHTPIN, DHTTYPE);

uint16_t eepromIndex = 0;
float tempC, humidity, averageTemp, averageHumid;
float totalTempF = 0.0, totalHumidF = 0.0;
int notificationSwitch = 3, notifButtonState;
unsigned int counter = 0, i = 0;
unsigned long timer;

void setup () {
  Serial.begin(9600);
  pinMode(notificationSwitch, INPUT);
  pinMode(LED_PIN, OUTPUT);
  timer = millis();
}

void loop () {
  tempC = tempSensor.readTemperature();
  humidity = tempSensor.readHumidity();
  
  totalTempF += tempC;
  totalHumidF += humidity;
  counter++;
  
  // For each 15 minutes, store to EEPROM
  if (millis() - timer >= ONE_HOUR / 4) {
    averageTemp = totalTempF / counter;
    averageHumid = totalHumidF / counter;
    
    // Debugging purpose
    Serial.print("Temp ");
    Serial.println(averageTemp);
    Serial.print("Humid ");
    Serial.println(averageHumid);
    
    // Format:
    // float: averageTemp
    // float: averageHumid

    // Sensor data
    EEPROM.writeFloat(eepromIndex, averageTemp);
    eepromIndex += sizeof(float); // Somehow cannot use EEPROM.write(eepromIndex++, ...) -> will store in the wrong address?
    EEPROM.writeFloat(eepromIndex, averageHumid);
    eepromIndex += sizeof(float);
    
    // Reset value
    totalTempF = totalHumidF = 0.0;
    counter = 0;
    timer = millis();
    
    if (eepromIndex >= 2 * sizeof(float) * NO_OF_HOURS * 4) {
      Serial.println("DONE!");
      notify();
      while (true);
    }
  }
  
  delay(100);
}

void notify () {
  notifButtonState = digitalRead(notificationSwitch);
  digitalWrite(LED_PIN, LOW);
  while (!notifButtonState) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
    
    notifButtonState = digitalRead(notificationSwitch);
  }
  
  digitalWrite(LED_PIN, LOW);
  sendData();
}

void sendData () {
  Serial.println("Reading Sensor Data from EEPROM:");
  for (int i = 0; i < 2 * sizeof(float) * NO_OF_HOURS * 4; i += 2 * sizeof(float)) {
    // Print time log
    Serial.print("Average Temperature: ");
    Serial.println(EEPROM.readFloat(i));
    Serial.print("Average Humidity: ");
    Serial.println(EEPROM.readFloat(i + sizeof(float)));
    Serial.println();
    
    delay(100);
  }
  
  Serial.println("FINISH READING!");
}
