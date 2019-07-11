#include <Ticker.h>
Ticker tickerWiFi;
Ticker tickerBME;
Ticker tickerSleep;

// Network
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define MAX_SRV_CLIENTS 1
#define CMDBUFFER_SIZE 32
#define SLEEP_TIME 10800 // Default time is 3h

//char *ssid = "scwook";
//char *ssid = "scwook-Pocket-Fi";
//char *password = "07170619";
char *ssid[3] = {"scwook", "scwook-Pocket-Fi", "raon_8_2.4g"};
char *password[3] = {"07170619", "07170619", "raon123456"};

ESP8266WebServer WebServer(80);
WiFiServer WifiServer(23);
//WiFiClient WifiServerClients[MAX_SRV_CLIENTS];
WiFiClient client;

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

#define OLED_RESET  13  // Reset Pin

SSD1306 OLED(0x3C, 4, 5);

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

int8_t wifiStatus = WL_DISCONNECTED;
int8_t wifiStrength = 0;
unsigned int sleepCount  =  SLEEP_TIME; // For Air Conditioner auto control

float humidity = -1.0;
float temperature = -1.0;
float pressure = -1.0;

String degree   = "\u00b0"; // Degree Unicode
String percent  = "\u0025"; // Percent Unicode

String acStateImage       = "snow_darkgray_46x46.png";    // Air Conditioner State Image, ON: white, OFF: darkgray
String sleepStateImage    = "sleep_darkgray_46x46.png";   // Sleep Mode State Image, ON: white, OFF: darkgray
String samsungVendorColor = "#FFFFFF";                    // Color, Selected: #FFFFFF, unselected: #808080
String lgVendorColor      = "#808080";

String sleepTime = "03:00:00";
//String wifiStatus = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(OLED_RESET, OUTPUT);
  digitalWrite(OLED_RESET, LOW);

  delay(500);
  digitalWrite(OLED_RESET, HIGH);

  delay(500);
  oledState = OLED.init();
  if ( !oledState ) {
    Serial.println("Could not find a valid OLED, check wiring!");
  }
  else {
    OLED.clear();
    OLED.drawXbm(0, 0, raon_symbol_width, raon_symbol_height, raon_symbol_bits);
    OLED.setFont(ArialMT_Plain_10);
    OLED.drawString(128 - OLED.getStringWidth("CONTROL"), 38, "CONTROL");

    //  OLED.setFont(ArialMT_Plain_24);
    //  OLED.drawString(0, 16, "Control");
    OLED.display();
    //  OLED.flipScreenVertically();
  }

  WiFi.mode(WIFI_STA);
  //  WiFi.begin(ssid[0], password[0]);

  unsigned int count = 0;
  OLED.setFont(ArialMT_Plain_10);

  for (int i = 0; i < 3; i++) {
    WiFi.begin(ssid[i], password[i]);

    OLED.clear();
    OLED.drawXbm(0, 0, raon_symbol_width, raon_symbol_height, raon_symbol_bits);
    OLED.setFont(ArialMT_Plain_10);
    OLED.drawString(128 - OLED.getStringWidth("CONTROL"), 38, "CONTROL");
    
    String strTmp = "Connecting to " + String(ssid[i]);
    OLED.drawString(0, 48, strTmp);
    OLED.display();
    
    delay(7000);

    if ( WiFi.status() == WL_CONNECTED) {
      wifiConnection = true;
      break;
    }
  }

//  for (int i = 0; i < 20; i++) {
//    if ( WiFi.status() == WL_CONNECTED ) {
//      wifiConnection = true;
//      break;
//    }
//
//    OLED.setFont(ArialMT_Plain_10);
//    String strTmp = "Connecting to " + String(ssid[0]);
//    OLED.drawString(0, 48, strTmp);
//    OLED.display();
//
//    count += 1;
//    Serial.print(".");
//    delay(1000);
//  }

  Serial.println("");
  if ( WiFi.status() == WL_CONNECTED ) {
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    WebServer.on("/", handleRoot);
    WebServer.on( "/readEnvValue", handleEnvValue);

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
  else {
    tickerBME.attach(1, readBME);
  }

  irsend.begin();
  tickerWiFi.attach(5, checkWiFiConnection);

  delay(500);
}

void checkWiFiConnection() {

  wifiStatus = WiFi.status();

  //  switch (WiFi.status()) {
  //    case WL_IDLE_STATUS:
  //      wifiStatus = "Idle Status";
  //      break;
  //
  //    case WL_NO_SSID_AVAIL:
  //      wifiStatus = "No SSID Availavle";
  //      break;
  //
  //    case WL_CONNECTED:
  //      wifiStatus = "Connected";
  //      break;
  //
  //    case WL_CONNECT_FAILED:
  //      wifiStatus = "Connection Failed";
  //      break;
  //
  //    case WL_CONNECTION_LOST:
  //      wifiStatus = "Connection Lost";
  //      break;
  //
  //    case WL_DISCONNECTED:
  //      wifiStatus = "Disconnected";
  //      break;
  //
  //    default:
  //      break;
  //  }

  //  int8_t rssi = WiFi.RSSI();
  //
  //  if (rssi > -55 && rssi <= 0 ) {
  //    wifiStrength = 4;
  //  }
  //  else if ( rssi > -65 && rssi <= -55 ) {
  //    wifiStrength = 3;
  //  }
  //  else if ( rssi > -75 && rssi <= -65 ) {
  //    wifiStrength = 2;
  //  }
  //  else if ( rssi > -85 && rssi <= -75 ) {
  //    wifiStrength = 1;
  //  }
  //  else {
  //    wifiStrength = 0;
  //  }
}

void readBME() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure();
}

void handleRoot() {
  //  float humidity = bme.readHumidity();
  //  float temperature = bme.readTemperature();

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
    OLED.displayOff();
    sleepMode = true;
    tickerSleep.attach(1, airConSleepTimer);
  }
  else if (WebServer.argName(0) == "sleepOff") {
    sleepStateImage = "sleep_darkgray_46x46.png";
    OLED.displayOn();
    sleepMode = false;
    tickerSleep.detach();
    sleepCount = SLEEP_TIME;
  }

  String t = String(temperature, 1) + "&#176" + "C";
  String h = String(humidity, 1) + "&#37";
  //  String c = String(count);

  String message = "";
  message += "<!DOCTYPE html>";
  message += "<html>";
  message += "<body>";
  message += "<meta charset=\"UTF-8\">";
  message += "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1.0\">";

  message += "<div style=\"position:relative;display:block;margin-left:auto;margin-right:auto;width:50%\">";
  message += "<img src=\"https://scwook.github.io/images/etc/remote_controller_bg_380x1000.png\" style=\"width:180px;height:500px\">";
  message += "<div style=\"position:absolute;top:45px;left:30px;font-size:10px;color:" + samsungVendorColor + ";font-family:sans-serif\">SAMSUNG</div>";
  message += "<div style=\"position:absolute;top:45px;left:135px;font-size:10px;color:" + lgVendorColor + ";font-family:sans-serif\">LG</div>";

  message += "<div id=\"time\" style=\"position:absolute;top:75px;left:70px;font-size:12px;color:white;font-family:sans-serif\">" + sleepTime + "</div>";

  message += "<img src=\"https://scwook.github.io/images/etc/" + acStateImage + "\" style=\"position:absolute;top:120px;left:40px;width:23px;height:23px\">";
  message += "<img src=\"https://scwook.github.io/images/etc/" + sleepStateImage + "\" style=\"position:absolute;top:120px;left:120px;width:23px;height:23px\">";

  message += "<img src=\"https://scwook.github.io/images/etc/temperature_color_86x144.png\" style=\"position:absolute;top:195px;left:30px;width:43px;height:72px\">";
  message += "<img src=\"https://scwook.github.io/images/etc/humidity_color_86x144.png\" style=\"position:absolute;top:195px;left:110px;width:43px;height:72px\" >";

  message += "<div id=\"temp\" style=\"position:absolute;top:270px;left:30px;font-size:15px;color:white;font-family:sans-serif\">" + t + "</div>";
  message += "<div id=\"humi\" style=\"position:absolute;top:270px;left:115px;font-size:15px;color:white;font-family:sans-serif\">" + h + "</div>";

  message += "<form method=\"get\" action=\"/\">";
  message += "<button name=\"powerOnOff\" type=\"submit\" style=\"position:absolute;bottom:100px;left:55px;border:none;background-color:Transparent\">";
  message += "<img src=\"https://scwook.github.io/images/etc/power_green_88x100.png\" style=\"width:44px;height:50px\"></button>";
  message += "<button name=\"changeVendor\" type=\"submit\" style=\"position:absolute;bottom:45px;left:65px;border:none;background-color:Transparent\">";
  message += "<img src=\"https://scwook.github.io/images/etc/change_white_50x44.png\" style=\"width:25px;height:22px\"></button>";
  message += "<button name=\"sleepOn\" type=\"submit\" style=\"position:absolute;bottom:51px;left:25px;border:none;background-color:Transparent;font-size:10px;color:white;font-family:sans-serif\">ON</button>";
  message += "<button name=\"sleepOff\" type=\"submit\" style=\"position:absolute;bottom:51px;left:120px;border:none;background-color:Transparent;font-size:10px;color:white;font-family:sans-serif\">OFF</button>";
  message += "</form>";
  message += "</div>";

  message += "<script>";
  message += "var myVar=setInterval(readValue,1000);";
  message += "function readValue(){";
  message += "var xhttp=new XMLHttpRequest();";
  message += "xhttp.onreadystatechange=function(){";
  message += "if(this.readyState==4&&this.status==200){";
  message += "var jsonValue=JSON.parse(this.responseText);";
  message += "document.getElementById(\"time\").innerHTML=jsonValue.SleepTime;";
  message += "document.getElementById(\"temp\").innerHTML=jsonValue.Temperature + \"&#176\" + \"C\";";
  message += "document.getElementById(\"humi\").innerHTML=jsonValue.Humidity + \"&#37\";}";
  message += "};";
  message += "xhttp.open(\"GET\",\"readEnvValue\",true);";
  message += "xhttp.send();}";
  message += "</script>";
  message += "</body>";
  message += "</html>";

  WebServer.send(200, "text/html", message);
}

void handleEnvValue() {

  String jsonObject = "{\"SleepTime\":\"" + sleepTime + "\",\"Temperature\":" + String(temperature, 1) + ",\"Humidity\":" + String(humidity, 1) + "}";

  WebServer.send(200, "text/plane", jsonObject);
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

//void processWiFiClient(float t, float h, float p) {
//  uint8_t i;
//
//  //check if there are any new clients
//  if (WifiServer.hasClient()) {
//    for (i = 0; i < MAX_SRV_CLIENTS; i++) {
//      //find free/disconnected spot
//      if (!WifiServerClients[i] || !WifiServerClients[i].connected()) {
//        if (WifiServerClients[i]) {
//          WifiServerClients[i].stop();
//        }
//        WifiServerClients[i] = WifiServer.available();
//        Serial1.print("New client: "); Serial1.print(i);
//        break;
//      }
//    }
//    //no free/disconnected spot so reject
//    if (i == MAX_SRV_CLIENTS) {
//      WiFiClient WifiServerClients = WifiServer.available();
//      WifiServerClients.stop();
//      Serial1.println("Connection rejected ");
//    }
//  }
//  //check clients for data
//  for (i = 0; i < MAX_SRV_CLIENTS; i++) {
//    if (WifiServerClients[i] && WifiServerClients[i].connected()) {
//
//      if (WifiServerClients[i].available()) {
//
//        //get data from the telnet client and push it to the UART
//        static char cmdBuffer[CMDBUFFER_SIZE] = "";
//        char c;
//        while (WifiServerClients[i].available()) {
//          c = processCharInput(cmdBuffer, WifiServerClients[i].read());
//
//          if ( c == '\n' ) {
//            //            Serial.write(cmdBuffer);
//            char val[10];
//
//            if ( strcmp("getTemperature", cmdBuffer) == 0 ) {
//              sprintf(val, " % f", t);
//              WifiServerClients[i].write(val);
//            }
//            else if (strcmp("getHumidity", cmdBuffer) == 0 )  {
//              sprintf(val, " % f", h);
//              WifiServerClients[i].write(val);
//            }
//            else if ( strcmp("getPressure", cmdBuffer) == 0 ) {
//              sprintf(val, " % f", p);
//              WifiServerClients[i].write(val);
//            }
//
//            cmdBuffer[0] = 0;
//          }
//        }
//      }
//    }
//  }
//}

void loop() {
  if (oledState) {
    String t = "T : " + String(temperature) + degree + "C";
    String h = "H : " + String(humidity) + percent;

    OLED.clear();

    OLED.setFont(ArialMT_Plain_24);
    OLED.drawString(0, 0, t);
    OLED.drawString(0, 0 + blueFontHeigh, h);
    //  OLED.drawXbm(0, yellowLineOffset, temperature_image_width, temperature_image_height, temperature_image_bits);
    OLED.drawXbm(0, 52, wifi_width, wifi_height, *wifi_bits[wifiStrength]);

    IPAddress ip = WiFi.localIP();
    String ipAddress = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    OLED.setFont(ArialMT_Plain_10);
    OLED.drawString(0, 52, ipAddress);

    //    OLED.drawString(24, 52, String(count));
    //    OLED.drawString(24, 52, wifiStatus);

    //    String p = String(rssi);
    //    OLED.drawString(34, 52, p);

    //    OLED.drawString(0, 56, "Hellow World");
    //    OLED.drawFastImage(112, 2, 8, 16, Bat816);

    OLED.display();
  }

  if (wifiConnection) {
    WebServer.handleClient();
    delay(100);
    //    processWiFiClient(temperature, humidity, pressure);
    wifiClient();
  }

  //  Serial.println("Loop End");

  //  if (count > 10800) {
  //    irsend.sendRaw(SAMSUNG_AC_ON29, sizeof(SAMSUNG_AC_ON29) / sizeof(SAMSUNG_AC_ON29[0]), IR_FREQ);
  //    delay(1000);
  //    irsend.sendRaw(SAMSUNG_AC_OFF_AFTER_1H, sizeof(SAMSUNG_AC_OFF_AFTER_1H) / sizeof(SAMSUNG_AC_OFF_AFTER_1H[0]), IR_FREQ);
  //
  //    //    Serial.println("AC ON");
  //    //    Serial.println("OFF Reservation");
  //
  //    count = 0;
  //  }
  //
  //  if (sleepMode) {
  //    count += 1;
  //  }

  //  Serial.println(count);
}

void airConSleepTimer() {

  if (sleepCount > 0) {

    int8_t hour = sleepCount / 3600;
    int8_t minute = (sleepCount / 60) % 60;
    int8_t second = sleepCount % 60;
    char remainTime[10];

    sprintf(remainTime, "%02d:%02d:%02d", hour, minute, second);

    sleepTime = String(remainTime);
    sleepCount -= 1;
  }
  else {
    irsend.sendRaw(SAMSUNG_AC_ON29, sizeof(SAMSUNG_AC_ON29) / sizeof(SAMSUNG_AC_ON29[0]), IR_FREQ);
    delay(1000);
    irsend.sendRaw(SAMSUNG_AC_OFF_AFTER_1H, sizeof(SAMSUNG_AC_OFF_AFTER_1H) / sizeof(SAMSUNG_AC_OFF_AFTER_1H[0]), IR_FREQ);

    sleepCount = SLEEP_TIME;
    sleepMode = false;
    tickerSleep.detach();
  }
}

void wifiClient() {
  uint8_t i;

  if (WifiServer.hasClient()) {
    client = WifiServer.available();
  }

  //check clients for data
  if (client && client.available())  {
    //get data from the telnet client and push it to the UART

    static char cmdBuffer[CMDBUFFER_SIZE] = "";
    char c;
    c = processCharInput(cmdBuffer, client.read());

    if ( c == '\n' ) {
      //            Serial.write(cmdBuffer);
      char val[10];

      if ( strcmp("getTemperature", cmdBuffer) == 0 ) {
        sprintf(val, " % f", temperature);
        client.write(val);
      }
      else if (strcmp("getHumidity", cmdBuffer) == 0 )  {
        sprintf(val, " % f", humidity);
        client.write(val);
      }
      else if ( strcmp("getPressure", cmdBuffer) == 0 ) {
        sprintf(val, " % f", pressure);
        client.write(val);
      }

      cmdBuffer[0] = 0;
    }
  }
}

