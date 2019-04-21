#include <Ticker.h>
Ticker tickerWiFi;
Ticker tickerSensor;
Ticker tickerBattery;

// LOX-02-S Oxygen Sensor Command Define
#include "CommandDefine.h"

// Network
#include <ESP8266WiFi.h>

#define MAX_SRV_CLIENTS 1
#define CMDBUFFER_SIZE 32

//  char *ssid = "scwook";
char *ssid = "scwook-Pocket-Fi";
char *password = "07170619";

WiFiServer WifiServer(23);
//WiFiClient WifiServerClients[MAX_SRV_CLIENTS];
WiFiClient client;

// SSD1306 OLED
#include "SSD1306.h"
#include "ImageCode.h"

#define OLED_RESET  13  // Reset Pin
SSD1306 OLED(0x3C, 12, 14); // address, SDA(DIN), SCL(CLK)
//SSD1306 OLED(0x3D, 12, 14);

unsigned int yellowLineOffset = 16;
boolean oledState = false;

// User Define Variable
boolean wifiConnection = false;
int8_t wifiStatus = WL_DISCONNECTED;
int8_t wifiStrength = 0;

int8_t batteryLevel = 0;

int8_t readCount = 0;

float ppO2        = -1.0;
float temperature = -1.0;
float pressure    = -1.0;
float oxygen      = -1.0;

String degree     = "\u00b0"; // Degree Unicode
String percent    = "\u0025"; // Percent Unicode
String subscript2 = "\u00b2"; // Subscript Number of 2

void setup() {
  // put your setup code here, to run once:
  //  WiFi.mode( WIFI_OFF );
  //  WiFi.forceSleepBegin();

  Serial1.begin(115200); // For Debug Message

  pinMode(OLED_RESET, OUTPUT);
  digitalWrite(OLED_RESET, LOW);

  delay(500);
  digitalWrite(OLED_RESET, HIGH);

  oledState = OLED.init();
  OLED.flipScreenVertically();

  if ( !oledState ) {
    Serial1.println("Could not find a valid OLED, check wiring!");
  }
  else {
    OLED.clear();
    OLED.drawXbm(0, yellowLineOffset, raon_symbol_width, raon_symbol_height, raon_symbol_bits);
    OLED.display();

    delay(2000);

    OLED.clear();
    OLED.setFont(ArialMT_Plain_24);
    OLED.drawString(8, 16, "CONTROL");
    OLED.display();
  }

  Serial.begin(9600); // For Sensor Communication

  Serial.write(STREAM_MODE, sizeof(STREAM_MODE) / sizeof(STREAM_MODE[0]));
  delay(100);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  unsigned int count = 0;
  for (int i = 0; i < 20; i++) {
    if ( WiFi.status() == WL_CONNECTED ) {
      wifiConnection = true;
      break;
    }

    Serial.print(".");
    OLED.setFont(ArialMT_Plain_10);
    OLED.drawString(count, 48, ".");
    OLED.display();

    count += 5;
    delay(500);
  }

  Serial1.println("");
  if ( WiFi.status() == WL_CONNECTED ) {
    Serial1.println("WiFi connected");
    Serial1.print("IP address: ");
    Serial1.println(WiFi.localIP());

    WifiServer.begin();
    WifiServer.setNoDelay(true);
    Serial1.println("WiFi Server Started");

  }
  else {
    Serial1.println("WiFi connection Failed");
  }

  if (Serial.available() > 0) {
    tickerSensor.attach(1, readSensor);
  }

  tickerWiFi.attach(5, checkWiFiConnection);
  tickerBattery.attach(10, readBattery);
}

void checkWiFiConnection() {

  wifiStatus = WiFi.status();

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

void readSensor() {

  //    Serial.write(REQ_O2, sizeof(REQ_O2) / sizeof(REQ_O2[0]));
  String value = Serial.readStringUntil('\n');
  //  delay(500);

  if ( value.length() == 40 ) {
    String pp    = value.substring(2, 8);
    String temp  = value.substring(11, 16);
    String pres  = value.substring(19, 23);
    String o2    = value.substring(26, 32);
    String error = value.substring(35, 39);

    ppO2         = pp.toFloat();
    temperature  = temp.toFloat();
    pressure     = pres.toFloat();
    oxygen       = o2.toFloat();

    //
  }

  readCount += 1;
  if (readCount > 3) {
    readCount = 0;
  }
}

void readBattery() {
  int value = analogRead(A0);

  if ( value < 800 ) {
    batteryLevel = BAT_EMPTY;
  }
  else if ( value >= 800 && value < 850 ) {
    batteryLevel = BAT_LOW;
  }
  else if ( value >= 850 && value < 900 ) {
    batteryLevel = BAT_HIGH;
  }
  else if ( value >= 900 ) {
    batteryLevel = BAT_FULL;
  }
}

//void processWiFiClient() {
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
//            if ( strcmp("getPartialPressure", cmdBuffer) == 0 ) {
//              sprintf(val, "%f", ppO2);
//              WifiServerClients[i].write(val);
//            }
//            else if ( strcmp("getTemperature", cmdBuffer) == 0 ) {
//              sprintf(val, "%f", temperature);
//              WifiServerClients[i].write(val);
//            }
//            else if ( strcmp("getPressure", cmdBuffer) == 0 ) {
//              sprintf(val, "%f", pressure);
//              WifiServerClients[i].write(val);
//            }
//            else if (strcmp("getOxygen", cmdBuffer) == 0 )  {
//              sprintf(val, "%f", oxygen);
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

void loop() {
  if (oledState) {
    OLED.clear();

    // Draw wifi icon
    if ( wifiStatus == WL_CONNECTED) {
      OLED.drawXbm(0, 0, wifi_symbole_width, wifi_symbole_height, wifi_symbol_bits);
      //OLED.drawXbm(50, 2, wifi_width, wifi_height, *wifi_bits[wifiStrength]);
    }

    // Draw EPICS connection icon
    if (client.connected()) {
      OLED.drawXbm(44, 0, epics_width, epics_height, epics_bits);
    }

    // Draw battery level icon
    OLED.drawXbm(112, 2, battery_width, battery_height, *battery_bits[batteryLevel]);

    // Draw oxygen icon
    OLED.drawXbm(0, 19, scl_width, scl_height, scl_bits);
    OLED.drawXbm(7, 29, data_reading_width, data_reading_height, *data_reading_bits[readCount]);

    // Draw oxygen value
    String o2 = String(oxygen, 2) + percent;
    OLED.setFont(ArialMT_Plain_24);
    OLED.drawString(43, 26, o2);
    //OLED.drawString(22, yellowLineOffset + 10, subscript2);

    OLED.setFont(ArialMT_Plain_10);

    // Draw thermometer icon
    //OLED.drawXbm(70, 42, thermometer_width, thermometer_height, thermometer_bits);

    // Draw temperature value
    String t = String(int(temperature)) + degree + "C";
    OLED.drawString(85, 0, t);

    // Display all value
    OLED.display();
  }

  //  delay(100);

  //      Serial1.println(oxygen);

  if (wifiConnection) {
    //          processWiFiClient();
    wifiClient();
  }

  //delay(500);

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

      if ( strcmp("getPartialPressure", cmdBuffer) == 0 ) {
        sprintf(val, "%f", ppO2);
        client.write(val);
      }
      else if ( strcmp("getTemperature", cmdBuffer) == 0 ) {
        sprintf(val, "%f", temperature);
        client.write(val);
      }
      else if ( strcmp("getPressure", cmdBuffer) == 0 ) {
        sprintf(val, "%f", pressure);
        client.write(val);
      }
      else if (strcmp("getOxygen", cmdBuffer) == 0 )  {
        sprintf(val, "%f", oxygen);
        client.write(val);
      }

      cmdBuffer[0] = 0;
    }
  }
}

/*
   //
  //  char *str = strtok("a b c", " ");
  //  Serial.println(str);
  //
  //  str = strtok(NULL, " ");

  //  Serial.println(str);

  //  String value = Serial.readStringUntil('\n');
  //  char tmp[100];
  //  value.toCharArray(tmp, 100);
  //
  //  char *O = strtok(tmp, " ");
  //  char *O_value = (NULL, " ");
*/
