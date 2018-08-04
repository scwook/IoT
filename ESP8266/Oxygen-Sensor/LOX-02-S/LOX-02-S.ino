#include <Ticker.h>
Ticker tickerWiFi;

// LOX-02-S Oxygen Sensor Command Define
#include "CommandDefine.h"

// Network
#include <ESP8266WiFi.h>

#define MAX_SRV_CLIENTS 1
#define CMDBUFFER_SIZE 32

char *ssid = "scwook";
char *password = "07170619";

WiFiServer WifiServer(23);
WiFiClient WifiServerClients[MAX_SRV_CLIENTS];

// SSD1306 OLED
#include "SSD1306.h"
#include "ImageCode.h"

SSD1306 OLED(0x3D, 4, 5);
boolean oledState = false;

// User Define Variable
boolean wifiConnection = false;
int8_t wifiStrength = 0;

float ppO2_f = -1.0;
float temp_f = -1.0;
float pres_f = -1.0;
float o2_f = -1.0;

void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200); // For Debug Message

  oledState = OLED.init();
  if ( !oledState ) {
    Serial.println("Could not find a valid OLED, check wiring!");
  }

  //  OLED.flipScreenVertically();

  OLED.clear();
  OLED.drawXbm(0, 0, raon_symbol_width, raon_symbol_height, raon_symbol_bits);
  OLED.setFont(ArialMT_Plain_10);
  OLED.drawString(128 - OLED.getStringWidth("CONTROL"), 38, "CONTROL");
  OLED.display();

  Serial.begin(9600); // For Sensor Communication

  while (!Serial) {
    ;
  }

  Serial.write(STREAM_MODE, sizeof(STREAM_MODE) / sizeof(STREAM_MODE[0]));
  delay(100);

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
    Serial1.println("WiFi connected");
    Serial1.print("IP address: ");
    Serial1.println(WiFi.localIP());

    WifiServer.begin();
    WifiServer.setNoDelay(true);
    Serial1.println("WiFi Server Started");

    tickerWiFi.attach(5, getRSSI);
  }
  else {
    Serial1.println("WiFi connection Failed");
  }

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

void processWiFiClient(float ppO2, float t, float p, float o2) {
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

            if ( strcmp("getPartialPressure", cmdBuffer) == 0 ) {
              sprintf(val, "%f", ppO2);
              WifiServerClients[i].write(val);
            }
            else if ( strcmp("getTemperature", cmdBuffer) == 0 ) {
              sprintf(val, "%f", t);
              WifiServerClients[i].write(val);
            }
            else if ( strcmp("getPressure", cmdBuffer) == 0 ) {
              sprintf(val, "%f", p);
              WifiServerClients[i].write(val);
            }
            else if (strcmp("getOxygen", cmdBuffer) == 0 )  {
              sprintf(val, "%f", o2);
              WifiServerClients[i].write(val);
            }

            cmdBuffer[0] = 0;
          }
        }
      }
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

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    //    Serial.write(REQ_O2, sizeof(REQ_O2) / sizeof(REQ_O2[0]));
    String value = Serial.readStringUntil('\n');
    delay(500);

    if ( value.length() == 40 ) {
      String ppO2 = value.substring(2, 8);
      String temp = value.substring(11, 16);
      String pres = value.substring(19, 23);
      String o2 = value.substring(26, 32);
      String error = value.substring(35, 39);

      ppO2_f = ppO2.toFloat();
      temp_f = temp.toFloat();
      pres_f = pres.toFloat();
      o2_f = o2.toFloat();
    }

    if (oledState) {
      OLED.clear();
      OLED.setFont(ArialMT_Plain_16);
//      OLED.drawString(0, 0, ppO2_f);
      OLED.drawString(0, 10, String(temp_f));
//      OLED.drawString(0, 20, pres_f);
      OLED.drawString(0, 30, String(o2_f));
//      OLED.drawString(0, 40, error);
//      OLED.drawString(0, 50, value);

      OLED.display();
    }
    
    delay(500);

    if (wifiConnection) {
      processWiFiClient(ppO2_f, temp_f, pres_f, o2_f);
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
