#define SERVO_PIN 5
#define BAUD_RATE 9600 // MUST BE 9600!!
#define DEBUG true

#include <Servo.h>
#include <SoftwareSerial.h>

const String WIFI_SSID = "";
const String WIFI_PASSWORD = "";
const String ESP8266_STATION_IP = "192.168.0.100";
const int SERVO_AC_ON = 90;
const int SERVO_AC_OFF = 118;

SoftwareSerial wifiSerial(11, 10); // because pin 0 and 1 are reserved for Serial over USB
Servo servo;

void setup() {
  setupWifi();
  setupServo();
}

void loop() {
  if (servo.attached()) {
    servo.detach();   
  }
  
  handleServerRequest();
  delay(300);
}

void setupServo() {
  servo.attach(SERVO_PIN);
  servo.write(SERVO_AC_OFF);
  delay(200);
}

void setupWifi() {
  Serial.begin(BAUD_RATE);
  wifiSerial.begin(BAUD_RATE);

  const String RESET = "AT+RST\r\n";
  const String WIFI_MODE = "AT+CWMODE=3\r\n";
  const String JOIN_AP = "AT+CWJAP=\"" + WIFI_SSID + "\",\"" + WIFI_PASSWORD + "\"\r\n";
  const String IP_ADDRESS = "AT+CIFSR\r\n";
  const String CONNECTION_MODE = "AT+CIPMUX=1\r\n";
  const String SET_SERVER = "AT+CIPSERVER=1,80\r\n";
  
  wifiSendData(RESET, 2000, DEBUG);
  wifiSendData(WIFI_MODE, 2000, DEBUG);
  wifiSendData(JOIN_AP, 5000, DEBUG);
  wifiSendData(IP_ADDRESS, 5000, DEBUG);
  wifiSendData(CONNECTION_MODE, 2000, DEBUG);
  wifiSendData(SET_SERVER, 2000, DEBUG);
}

void handleServerRequest() {
  if (wifiSerial.available()) {
    if (wifiSerial.find("+IPD,")) {
      delay(2000);
      int connectionId = wifiSerial.read() - 48;
      int servoPosition;
      String response = "false";
      
      if (wifiSerial.find("?ac=on")) {
        servoPosition = SERVO_AC_ON;
        response = "true";
      } else {
        servoPosition = SERVO_AC_OFF;
        response = "true";
      }

      delay(200);
      sendResponse(connectionId, "true");
      closeConnection(connectionId);

      delay(100);
      servo.attach(SERVO_PIN);
      delay(100);

      Serial.println(servoPosition);
      for (int i = 0; i < 10; i++) {
        servo.write(servoPosition);
        delay(100); 
      }
    }
  }
}

void serialDebugging() {
  if (wifiSerial.available()) {
    while (wifiSerial.available()) {
      Serial.write(wifiSerial.read());
    }
  }

  // This loop receives the COMMAND from the Serial monitor and send it to the ESP8266
  if (Serial.available()) {
    // This delay is needed to wait for most of the command given from the Serial monitor to be received
    // before sending it into ESP826
    delay(100);

    String command = "";
    while (Serial.available()) {
      command += (char) Serial.read();
    }

    wifiSerial.println(command);
    Serial.println(command);
  }
}

void sendResponse(int connectionId, String content) {
  String sendDataCommand = "AT+CIPSEND=";
  sendDataCommand += connectionId;
  sendDataCommand += ",";
  sendDataCommand += content.length();
  sendDataCommand += "\r\n";
  wifiSendData(sendDataCommand, 3000, DEBUG);
  wifiSendData(content, 3000, DEBUG);
}

void closeConnection(int connectionId) {
  String closeConnectionCommand = "AT+CIPCLOSE=";
  closeConnectionCommand += connectionId;
  closeConnectionCommand += "\r\n";
  wifiSendData(closeConnectionCommand, 3000, DEBUG);
}

void wifiSendData(String command, const int timeout, boolean debug) {
  String response = "";
  wifiSerial.print(command);

  delay(timeout);
  while (wifiSerial.available()) {
    char c = wifiSerial.read();
    response += c;
  }

  if (debug) {
    Serial.println(response);
  }
}

