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

#define IR_FREQ 38  // IR Frequency is 38kHz
#define IR_LED  15  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

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
#define ON   true
#define OFF  false

boolean wifiConnection = false;
boolean acPower     = OFF;    // Air Conditioner state, ON: true, OFF: false
boolean bmeState    = false;  // BME280 Sensor connection state, success: true, fail: false
boolean oledState   = false;
boolean sleepMode   = false;
boolean vendorMode  = false;  // Remote Controller Vendor, SAMSUNG: false, LG: true;

int8_t wifiStrength = 0;
unsigned int count  = 0; // For Air Conditioner auto control

String acStateImage       = "snow_darkgray_46x46.png";    // Air Conditioner State Image, ON: white, OFF: darkgray
String sleepStateImage    = "sleep_darkgray_46x46.png";   // Sleep Mode State Image, ON: white, OFF: darkgray
String samsungVendorColor = "#FFFFFF";                    // Color, Selected: #FFFFFF, unselected: #808080
String lgVendorColor      = "#808080";

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

  if (WebServer.argName(0) == "powerOnOff") {
    //    int state = WebServer.arg(0).toInt();

    if (acPower) {
      if (vendorMode) { // LG
        irsend.sendRaw(LG_AC_ONOFF, sizeof(LG_AC_ONOFF) / sizeof(LG_AC_ONOFF[0]), IR_FREQ);

      }
      else { // SAMSUNG
        irsend.sendRaw(SAMSUNG_AC_OFF, sizeof(SAMSUNG_AC_OFF) / sizeof(SAMSUNG_AC_OFF[0]), IR_FREQ);

      }

      acStateImage = "snow_darkgray_46x46.png";
      acPower = OFF;
    }
    else {
      if (vendorMode) { // LG
        irsend.sendRaw(LG_AC_ONOFF, sizeof(LG_AC_ONOFF) / sizeof(LG_AC_ONOFF[0]), IR_FREQ);
      }
      else { // SAMSUNG
        irsend.sendRaw(SAMSUNG_AC_ON28, sizeof(SAMSUNG_AC_ON28) / sizeof(SAMSUNG_AC_ON28[0]), IR_FREQ);
      }

      acStateImage = "snow_white_46x46.png";
      acPower = ON;
    }
  }
  else if (WebServer.argName(0) == "changeVendor") {
    if (vendorMode) { // LG
      samsungVendorColor = "#FFFFFF";
      lgVendorColor = "#808080";
      vendorMode = false;
    }
    else { // SAMSUNG
      samsungVendorColor = "#808080";
      lgVendorColor = "#FFFFFF";
      vendorMode = true;
    }
  }
  else if (WebServer.argName(0) == "sleepOn") {
    sleepStateImage = "sleep_white_46x46.png";
    sleepMode = true;
  }
  else if (WebServer.argName(0) == "sleepOff") {
    sleepStateImage = "sleep_darkgray_46x46.png";
    sleepMode = false;
  }

  String t = String(temperature) + "&#176" + "C";
  String h = String(humidity) + "&#37";
  String message = "";
  message += "<!DOCTYPE html>";
  message += "<html>";
  message += "<body>";
  message += "<meta charset=\"UTF-8\">";
  message += "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\">";

  message += "<div style=\"position:relative;display:block;margin-left:auto;margin-right:auto;width:50%\">";
  message += "<img src=\"https://scwook.github.io/images/etc/remote_controller_bg_320x900.png\" style=\"width:160px;height:450px\">";
  message += "<div style=\"position:absolute;top:25px;left:20px;font-size:10px;color:" + samsungVendorColor + ";font-family:sans-serif\">SAMSUNG</div>";
  message += "<div style=\"position:absolute;top:25px;left:125px;font-size:10px;color:" + lgVendorColor + ";font-family:sans-serif\">LG</div>";

  message += "<img src=\"https://scwook.github.io/images/etc/" + acStateImage + "\" style=\"position:absolute;top:100px;left:30px;width:23px;height:23px\">";
  message += "<img src=\"https://scwook.github.io/images/etc/" + sleepStateImage + "\" style=\"position:absolute;top:100px;left:110px;width:23px;height:23px\">";

  message += "<img src=\"https://scwook.github.io/images/etc/temperature_color_86x144.png\" style=\"position:absolute;top:175px;left:20px;width:43px;height:72px\">";
  message += "<img src=\"https://scwook.github.io/images/etc/humidity_color_86x144.png\" style=\"position:absolute;top:175px;left:100px;width:43px;height:72px\" >";

  message += "<div style=\"position:absolute;top:250px;left:20px;font-size:15px;color:white;font-family:sans-serif\">" + t + "</div>";
  message += "<div style=\"position:absolute;top:250px;left:100px;font-size:15px;color:white;font-family:sans-serif\">" + h + "</div>";

  message += "<form method=\"get\" action=\"/\">";
  message += "<button name=\"powerOnOff\" type=\"submit\" style=\"position:absolute;bottom:75px;left:45px;border:none;background-color:Transparent\">";
  message += "<img src=\"https://scwook.github.io/images/etc/power_green_88x100.png\" style=\"width:44px;height:50px\"></button>";
  message += "<button name=\"changeVendor\" type=\"submit\" style=\"position:absolute;bottom:15px;left:55px;border:none;background-color:Transparent\">";
  message += "<img src=\"https://scwook.github.io/images/etc/change_white_50x44.png\" style=\"width:25px;height:22px\"></button>";
  message += "<button name=\"sleepOn\" type=\"submit\" style=\"position:absolute;bottom:21px;left:15px;border:none;background-color:Transparent;font-size:10px;color:white;font-family:sans-serif\">ON</button>";
  message += "<button name=\"sleepOff\" type=\"submit\" style=\"position:absolute;bottom:21px;left:110px;border:none;background-color:Transparent;font-size:10px;color:white;font-family:sans-serif\">OFF</button>";
  message += "</form>";
  message += "</div>";

  //  message += "<button name=\"ACstatus\" type=\"submit\" style=\"background-color:#9ACD32;border:none;color:white;font-size:20px;font-weight:bold;width:64px;height:64px;border-radius:50%\" value=\"1\">ON</button>";
  //  message += "<button name=\"ACstatus\" type=\"submit\" style=\"background-color:#FF6347;border:none;color:white;font-size:20px;font-weight:bold;width:64px;height:64px;border-radius:50%\" value=\"0\">OFF</button>";
  //  message += "</form >";

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

  if (wifiConnection) {
    WebServer.handleClient();
    delay(500);
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

  if (sleepMode) {
    count += 1;
  }
  
  //  Serial.println(count);
}

