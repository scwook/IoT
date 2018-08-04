#include <Ticker.h>
Ticker tickerWiFi;

// Network
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define MAX_SRV_CLIENTS 1
#define CMDBUFFER_SIZE 32

char *ssid = "scwook";
char *password = "07170619";

//char *ssid = "scwook-Pocket-Fi";
//char *password = "07170619";

ESP8266WebServer WebServer(80);
WiFiServer WifiServer(23);
WiFiClient WifiServerClients[MAX_SRV_CLIENTS];

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

SSD1306 OLED(0x3D, 4, 5);
unsigned int yellowLineOffset = 16;
unsigned int yellowFontHeigh = 0;
unsigned int blueFontHeigh = 24;

//#define SEALEVELPRESSURE_HPA (1013.25)

// User Define Variable
#define AC_ON   true
#define AC_OFF  false

boolean wifiConnection = false;
boolean acState = AC_OFF; // Air Conditioner state, ON: true, OFF: false
boolean bmeState = false; // BME280 Sensor connection state, success: true, fail: false
boolean oledState = false;

int8_t wifiStrength = 0;

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
  OLED.setFont(ArialMT_Plain_10);
  OLED.drawString(128 - OLED.getStringWidth("CONTROL"), 38, "CONTROL");

  //  OLED.setFont(ArialMT_Plain_24);
  //  OLED.drawString(0, 16, "Control");
  OLED.display();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  for (int i = 0; i < 10; i++) {
    if ( WiFi.status() == WL_CONNECTED ) {
      wifiConnection = true;
      break;
    }

    Serial.print(".");
    delay(500);
  }

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

    tickerWiFi.attach(5, getRSSI);
  }
  else {
    Serial.println("WiFi connection Failed");
  }

  bmeState = bme.begin(BME280_ADDR);
  if (!bmeState) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }

  irsend.begin();

  delay(1500);
}

void getRSSI() {
  int8_t rssi = WiFi.RSSI();

  if (rssi > -55 ) {
    wifiStrength = 4;
  }
  else if ( rssi > -65 && rssi <= -55 ) {
    wifiStrength = 3;
  }
  else if ( rssi > -75 && rssi <= -65 ) {
    wifiStrength = 2;
  }
  else if ( rssi > -85 && rssi <= -75 ) {
    wifiStrength = 1;
  }
  else {
    wifiStrength = 0;
  }
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
  message += "<figure style=\"float:left;margin-right:0%;margin-bottom:0.5em\">";
  message += "<img src=\"https://scwook.github.io/images/etc/temperature_130x240.png\" width=\"65\" height=\"120\">";
  message += "<figcaption style=\"text-align:center;font-size:200%\">";
  message += temperature;
  message += "</figcaption>";
  message += "</figure>";
  message += "<figure style=\"float:left;margin-right:0%;margin-bottom:0.5em\">";
  message += "<img src=\"https://scwook.github.io/images/etc/humidity_130x240.png\" width=\"65\" height=\"120\" >";
  message += "<figcaption style=\"text-align:center;font-size:200%\">";
  message += humidity;
  message += "</figcaption>";
  message += "</figure>";

  message += "<p style=\"clear:both\">";

  message += "<br />";
  message += "Count ";
  message += count;

  message += "<br />";
  message += "Air Conditioner is ";
  message += (acState ? "ON" : "OFF");

  message += "<br />";
  message += "<form method=\"get\" action=\"/\">";
  message += "<button name=\"ACstatus\" type=\"submit\" style=\"background-color:#9ACD32;border:none;color:white;font-size:20px;font-weight:bold;width:64px;height:64px;border-radius:50%\" value=\"1\">ON</button>";
  message += "<button name=\"ACstatus\" type=\"submit\" style=\"background-color:#FF6347;border:none;color:white;font-size:20px;font-weight:bold;width:64px;height:64px;border-radius:50%;margin:10px\" value=\"0\">OFF</button>";
  message += "</form >";

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
              sprintf(val, " % f", t);
              WifiServerClients[i].write(val);
            }
            else if (strcmp("getHumidity", cmdBuffer) == 0 )  {
              sprintf(val, " % f", h);
              WifiServerClients[i].write(val);
            }
            else if ( strcmp("getPressure", cmdBuffer) == 0 ) {
              sprintf(val, " % f", p);
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
  //  if (t > 30.0) {
  //    if (count > 60) {
  //      if (!acState) {
  //        irsend.sendRaw(SAMSUNG_AC_ON28, sizeof(SAMSUNG_AC_ON28) / sizeof(SAMSUNG_AC_ON28[0]), 38);
  //        acState = true;
  //        count = 0;
  //      }
  //    }
  //    else {
  //      count += 1;
  //    }
  //
  //  }
  //  else if (t < 28.0) {
  //    if (count > 60) {
  //      if (acState) {
  //        irsend.sendRaw(SAMSUNG_AC_OFF, sizeof(SAMSUNG_AC_OFF) / sizeof(SAMSUNG_AC_OFF[0]), 38);
  //        acState = false;
  //        count = 0;
  //      }
  //    }
  //    else {
  //      count += 1;
  //    }
  //  }
  //  else {
  //    count = 0;
  //  }
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
    OLED.drawXbm(0, 52, wifi_width, wifi_height, *wifi_bits[wifiStrength]);

    OLED.setFont(ArialMT_Plain_10);
    OLED.drawString(24, 52, String(count));

    //    String p = String(rssi);
    //    OLED.drawString(34, 52, p);

    //    OLED.drawString(0, 56, "Hellow World");
    //    OLED.drawFastImage(112, 2, 8, 16, Bat816);

    OLED.display();

  }

  delay(500);

  if (wifiConnection) {
    WebServer.handleClient();
    processWiFiClient(temperature, humidity, pressure);
  }

  //  airConAutoControl();

  //  Serial.println("Loop End");

  delay(500);

  if (count > 10800) {
    irsend.sendRaw(SAMSUNG_AC_ON28, sizeof(SAMSUNG_AC_ON28) / sizeof(SAMSUNG_AC_ON28[0]), 38);
    delay(1000);
    irsend.sendRaw(SAMSUNG_AC_OFF_AFTER_1H, sizeof(SAMSUNG_AC_OFF_AFTER_1H) / sizeof(SAMSUNG_AC_OFF_AFTER_1H[0]), 38);

    //    Serial.println("AC ON");
    //    Serial.println("OFF Reservation");

    count = 0;
  }

  count += 1;
  //  Serial.println(count);
}

