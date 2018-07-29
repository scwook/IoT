#include <Ticker.h>

Ticker tickerWiFi;

// Network
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define MAX_SRV_CLIENTS 1
#define CMDBUFFER_SIZE 32

char *ssid = "scwook";
char *password = "07170619";

ESP8266WebServer WebServer(80);
WiFiServer WifiServer(23);
WiFiClient WifiServerClients[MAX_SRV_CLIENTS];

//#ifndef UNIT_TEST
//#include <Arduino.h>
//#endif

// IR Sensor
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "IRCode.h"

#define IR_LED 15  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.

// BME280 I2C
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME280_ADDR 0x76
Adafruit_BME280 bme;

// SSD1306 OLED
#include "SSD1306.h"
#include "ImageCode.h"

SSD1306 OLED(0x3C, 4, 5);
unsigned int yellowLineOffset = 16;
unsigned int yellowFontHeigh = 0;
unsigned int blueFontHeigh = 24;

//#define SEALEVELPRESSURE_HPA (1013.25)

// User Define Variable

boolean wifiConnection = false;
boolean acState = false; // Air Conditioner state, ON: true, OFF: false
boolean bmeState = false; // BME280 Sensor connection state, success: true, fail: false
boolean oledState = false;

int32_t rssi = 0;

unsigned int count = 0; // For Air Conditioner auto control

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  oledState = OLED.init();
  if ( !oledState ) {
    Serial.println("Could not find a valid OLED, check wiring!");
  }

  //  OLED.flipScreenVertically();

  OLED.clear();
  OLED.drawXbm(0, 0, raon_symbol_width, raon_symbol_height, raon_symbol_bits);
  OLED.drawXbm(0, 48, wifi_width, wifi_height, *wifi_bits[0]);

  //  OLED.setFont(ArialMT_Plain_24);
  //  OLED.drawString(0, 16, "Control");
  OLED.display();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  //  while ( WiFi.status() != WL_CONNECTED) {
  //    delay(500);
  //    Serial.print(".");
  //  }

  for (int i = 0; i < 10; i++) {
    if ( WiFi.status() == WL_CONNECTED ) {
      wifiConnection = true;
      break;
    }

    Serial.print(".");
    delay(500);
  }

  tickerWiFi.attach(5, getRSSI);

  Serial.println("");
  if ( WiFi.status() == WL_CONNECTED ) {
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    WebServer.on("/", handleRoot);
    WebServer.on("/ac.cgi", handleONOFF);

    WebServer.begin();
    Serial.println("HTTP Server Started");

    WifiServer.begin();
    WifiServer.setNoDelay(true);
    Serial.println("WiFi Server Started");
  }
  else {
    Serial.println("WiFi connection Failed");
  }

  bmeState = bme.begin(BME280_ADDR);
  if (!bmeState) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }

  irsend.begin();

  delay(3000);
}

void getRSSI() {
  rssi = WiFi.RSSI();

  Serial.print("RSSI = ");
  Serial.println(rssi);
}

void handleRoot() {
  float humidity = bme.readHumidity();
  float temperature = bme.readTemperature();

  //  server.sendHeader("Refresh", "3");

  if ( isnan(humidity) || isnan(temperature) ) {
    WebServer.send(200, "text/plain", "Error in reading sensor.");
  }

  if (WebServer.argName(0) == "ACstatus") {
    int state = WebServer.arg(0).toInt();

    if (state) {
      irsend.sendRaw(SAMSUNG_AC_ON28, sizeof(SAMSUNG_AC_ON28) / sizeof(SAMSUNG_AC_ON28[0]), 38);
      acState = true;
    }
    else {
      irsend.sendRaw(SAMSUNG_AC_OFF, sizeof(SAMSUNG_AC_OFF) / sizeof(SAMSUNG_AC_OFF[0]), 38);
      acState = false;
    }
  }

  String message = "";
  message += "<html>";
  message += "<body>";
  message += "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0,minimum-scale=1.0,maximum-scale=1.0\">";
  message += "Temperature : ";
  message += temperature;
  message += ", Humidity : ";
  message += humidity;

  message += "<br />";
  message += "Count ";
  message += count;

  message += "<br />";
  message += "Air Conditioner is ";
  message += (acState ? "ON" : "OFF");

  message += "<br />";
  message += "<FORM method=\"get\" action=\"/\">";
  message += "<P><INPUT type=\"radio\" name=\"ACstatus\" value=\"1\">Turn ON";
  message += "<P><INPUT type=\"radio\" name=\"ACstatus\" value=\"0\">Turn OFF";
  message += "<P><INPUT type=\"submit\" value=\"Submit\"> </FORM>";

  message += "</body>";
  message += "</html>";

  WebServer.send(200, "text/html", message);
}



void handleONOFF() {
  if (WebServer.argName(0) == "ACstatus") {
    int state = WebServer.arg(0).toInt();

    if (state) {
      irsend.sendRaw(SAMSUNG_AC_ON28, sizeof(SAMSUNG_AC_ON28) / sizeof(SAMSUNG_AC_ON28[0]), 38);
    }
    else {
      irsend.sendRaw(SAMSUNG_AC_OFF, sizeof(SAMSUNG_AC_OFF) / sizeof(SAMSUNG_AC_OFF[0]), 38);
    }

    //    String message = "";
    //    message += "<html>";
    //    message += "<body>";
    //    message += "Air Conditioner is ";
    //    message += (state ? "ON." : "OFF.");
    //    message += "</body>";
    //    message += "</html>";
    //
    //    server.send(200, "text/html", message);
  }
}

char processCharInput(char* cmdBuffer, const char c)
{
  //Store the character in the input buffer
  if (c >= 32 && c <= 126) //Ignore control characters and special ascii characters
  {
    if (strlen(cmdBuffer) < CMDBUFFER_SIZE)
    {
      strncat(cmdBuffer, &c, 1);   //Add it to the buffer
    }
    else
    {
      return '\n';
    }
  }
  else if ((c == 8 || c == 127) && cmdBuffer[0] != 0) //Backspace
  {

    cmdBuffer[strlen(cmdBuffer) - 1] = 0;
  }

  return c;
}

void processWiFiClient(float t, float h, float p) {
  uint8_t i;

  //check if there are any new clients
  if (WifiServer.hasClient()) {
    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
      //find free/disconnected spot
      if (!WifiServerClients[i] || !WifiServerClients[i].connected()) {
        if (WifiServerClients[i]) {
          WifiServerClients[i].stop();
        }
        WifiServerClients[i] = WifiServer.available();
        Serial1.print("New client: "); Serial1.print(i);
        break;
      }
    }
    //no free/disconnected spot so reject
    if (i == MAX_SRV_CLIENTS) {
      WiFiClient WifiServerClients = WifiServer.available();
      WifiServerClients.stop();
      Serial1.println("Connection rejected ");
    }
  }
  //check clients for data
  for (i = 0; i < MAX_SRV_CLIENTS; i++) {
    if (WifiServerClients[i] && WifiServerClients[i].connected()) {

      if (WifiServerClients[i].available()) {

        //get data from the telnet client and push it to the UART
        static char cmdBuffer[CMDBUFFER_SIZE] = "";
        char c;
        while (WifiServerClients[i].available()) {
          c = processCharInput(cmdBuffer, WifiServerClients[i].read());

          if ( c == '\n' ) {
            //            Serial.write(cmdBuffer);
            char val[10];

            if ( strcmp("getTemperature", cmdBuffer) == 0 ) {
              sprintf(val, "%f", t);
              WifiServerClients[i].write(val);
            }
            else if (strcmp("getHumidity", cmdBuffer) == 0 )  {
              sprintf(val, "%f", h);
              WifiServerClients[i].write(val);
            }
            else if ( strcmp("getPressure", cmdBuffer) == 0 ) {
              sprintf(val, "%f", p);
              WifiServerClients[i].write(val);
            }

            cmdBuffer[0] = 0;
          }
        }
      }
    }
  }
}

void airConAutoControl(float t) {
  if (t > 30.0) {
    if (count > 60) {
      if (!acState) {
        irsend.sendRaw(SAMSUNG_AC_ON28, sizeof(SAMSUNG_AC_ON28) / sizeof(SAMSUNG_AC_ON28[0]), 38);
        acState = true;
        count = 0;
      }
    }
    else {
      count += 1;
    }

  }
  else if (t < 28.0) {
    if (count > 60) {
      if (acState) {
        irsend.sendRaw(SAMSUNG_AC_OFF, sizeof(SAMSUNG_AC_OFF) / sizeof(SAMSUNG_AC_OFF[0]), 38);
        acState = false;
        count = 0;
      }
    }
    else {
      count += 1;
    }
  }
  else {
    count = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  float temperature = -1.0;
  float humidity = -1.0;
  float pressure = -1.0;

  if (oledState) {
    if (bmeState) {
      temperature = bme.readTemperature();
      humidity = bme.readHumidity();
      pressure = bme.readPressure();
    }

    String degree = "\u00b0";
    String t = "T : " + String(temperature) + degree + "C";

    String percent = "\u0025";
    String h = "H : " + String(humidity) + percent;

    OLED.clear();

    OLED.setFont(ArialMT_Plain_24);
    OLED.drawString(0, 0, t);
    OLED.drawString(0, 0 + blueFontHeigh, h);
    //  OLED.drawXbm(0, yellowLineOffset, temperature_image_width, temperature_image_height, temperature_image_bits);
    OLED.drawXbm(0, 52, wifi_width, wifi_height, *wifi_bits[count]);

    //    OLED.setFont(ArialMT_Plain_10);
    //    OLED.drawString(0, 56, "Hellow World");
    //    OLED.drawFastImage(112, 2, 8, 16, Bat816);

    OLED.display();

    delay(500);
    count += 1;


    if( count > 3 ) {
      count = 0;
    }
  }

  if (wifiConnection) {
    WebServer.handleClient();
    //  airConAutoControl(temperature);
    processWiFiClient(temperature, humidity, pressure);
  }

//  Serial.println("Loop End");

  delay(500);
}

