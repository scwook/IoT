#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#include "SSD1306.h"

#define IR_LED 13  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
#define MAX_SRV_CLIENTS 1
#define CMDBUFFER_SIZE 32
#define SEALEVELPRESSURE_HPA (1013.25)

IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.
boolean AC_state = false;

Adafruit_BME280 bme;

SSD1306 OLED(0x3D, 4, 5);
unsigned int yellowLineOffset = 16;
unsigned int yellowFontHeigh = 0;
unsigned int blueFontHeigh = 24;

char *ssid = "scwook";
char *password = "07170619";

unsigned int count = 0;

ESP8266WebServer WebServer(80);
WiFiServer WifiServer(23);
WiFiClient WifiServerClients[MAX_SRV_CLIENTS];

#define temperature_image_width 13
#define temperature_image_height 20
static unsigned char temperature_image_bits[] = {
  0x00, 0x00, 0xe0, 0x00, 0x10, 0x01, 0x90, 0x01, 0x10, 0x01, 0x90, 0x01,
  0x10, 0x01, 0x10, 0x01, 0x90, 0x01, 0x10, 0x01, 0x18, 0x03, 0x0c, 0x06,
  0x04, 0x04, 0x02, 0x08, 0x02, 0x08, 0x06, 0x0c, 0x04, 0x04, 0x0c, 0x06,
  0xf8, 0x01, 0x00, 0x00
};

const uint8_t Bat816[16] = {
  0x0F, 0xFE, 0x30, 0x02, 0x26, 0xDA, 0x26, 0xDA, 0x26, 0xDA, 0x26, 0xDA, 0x30, 0x02, 0x0F, 0xFE
};


uint16_t acON[] = { 2561, 698, 1239, 4547, 553, 3993
                    , 500, 1756, 501, 657, 503, 605
                    , 532, 1998, 236, 879, 263, 1835
                    , 427, 1786, 529, 2991, 328, 2042
                    , 255, 655, 505, 657, 503, 580
                    , 529, 2998, 340, 939, 214, 665
                    , 482, 658, 478, 709, 451, 3023
                    , 285, 720, 451, 1790, 528, 1834
                    , 396, 1812, 231, 4266, 528,  2002696
                    , 4211, 6858, 467, 1798, 525, 1993
                    , 238, 1925, 293, 665, 483, 740
                    , 441, 657, 450, 6360, 264, 2055
                    , 398, 6352, 451, 4224, 279, 5356
                    , 179,  1705684
                    , 3038, 8932, 509, 1473, 509, 505
                    , 486, 506, 490, 501, 485, 507
                    , 485, 506, 486, 505, 485, 508
                    , 485, 505, 485, 1473, 509, 507
                    , 485, 507, 490, 1491, 486, 1474
                    , 509, 1495, 486, 1471, 510, 506
                    , 486, 1476, 505, 1474, 508, 1495
                    , 486, 1474, 509, 1495, 486, 1476
                    , 506, 1471, 510, 1471, 510, 506
                    , 486, 505, 485, 505, 486, 483
                    , 508, 505, 489, 502, 485, 507
                    , 485, 482, 509, 505, 486, 506
                    , 485, 506, 484, 505, 486, 1473
                    , 508, 506, 485, 486, 505, 1471
                    , 510, 1474, 508, 506, 485, 1469
                    , 512, 1472, 509, 510, 481, 511
                    , 480, 505, 485, 506, 485, 506
                    , 485, 506, 485, 506, 485, 1473
                    , 507, 1480, 504, 1494, 486, 1474
                    , 509,   217550
                    , 1664, 451, 1704, 5200, 528, 1832
                    , 452, 4176, 317, 683, 424, 766
                    , 293, 3114, 292, 1861, 529, 1735
                    , 502, 1840, 339, 912, 309, 1762
                    , 528, 685, 453, 655, 477, 2921
                    , 456, 1868, 452, 597, 561, 576
                    , 531, 1859, 362, 2074, 178, 848
                    , 291, 1766, 502, 4193, 236, 1876
                    , 453, 1786, 419, 2045, 318
                  };

uint16_t acON28[] = {666, 18054, 3076, 9084,  596,  430
                     ,  568, 1411,  594,  433,  568,  434
                     ,  568,  435,  569,  434,  568,  433
                     ,  569,  433,  569,  434,  573, 1431
                     ,  569,  433,  568,  436,  568, 1411
                     ,  593,  433,  569,  434,  569, 1435
                     ,  573, 1431,  570, 1410,  594, 1412
                     ,  592, 1436,  569,  434,  567,  434
                     ,  569,  434,  568,  435,  568,  433
                     ,  569,  434,  568,  434,  568,  434
                     ,  569,  434,  567,  434,  569,  435
                     ,  567,  435,  572,  430,  568,  434
                     ,  568,  434,  568,  434,  568,  435
                     ,  568,  433,  570,  434,  568,  408
                     ,  593,  434,  569,  409,  597,  405
                     ,  593,  434,  569,  410,  592,  434
                     ,  569,  433,  568,  434,  569,  434
                     ,  568,  433,  569,  434,  569,  433
                     ,  573, 1432,  568, 1436,  569, 1410
                     ,  594, 1412,  593, 2888, 3073, 9091
                     ,  589, 1435,  568,  434,  569,  434
                     ,  568,  434,  568,  434,  570,  433
                     ,  568,  433,  569,  434,  568,  434
                     ,  569, 1411,  593,  435,  567,  435
                     ,  568, 1436,  572,  430,  569, 1413
                     ,  591, 1413,  590, 1412,  594, 1411
                     ,  593, 1411,  594, 1409,  595,  434
                     ,  568,  433,  569,  435,  568,  434
                     ,  568,  434,  569,  433,  569,  434
                     ,  572,  430,  568,  435,  567,  435
                     ,  568,  433,  569,  434,  569,  432
                     ,  570,  433,  569,  434,  568,  434
                     ,  568,  433,  573,  431,  568,  434
                     ,  568,  435,  567,  433,  570,  433
                     ,  569,  410,  591,  435,  568,  434
                     ,  567,  435,  568,  434,  569,  434
                     ,  568,  433,  570,  433,  569,  434
                     ,  568,  434,  568,  434,  568,  435
                     ,  567,  434,  568,  435,  568, 2886
                     , 3075, 9094,  585, 1437,  568,  434
                     ,  568,  435,  567,  435,  567,  435
                     ,  568,  433,  569,  434,  569,  433
                     ,  568,  434,  569, 1435,  569,  434
                     ,  568,  434,  569, 1416,  589,  432
                     ,  570, 1436,  568, 1436,  569,  433
                     ,  569, 1436,  568, 1411,  593, 1412
                     ,  594, 1413,  591, 1409,  595, 1412
                     ,  593, 1415,  590, 1411,  593,  434
                     ,  568,  435,  567,  435,  568, 1410
                     ,  595, 1435,  568, 1416,  589,  435
                     ,  567,  435,  567,  434,  568,  434
                     ,  569,  434,  569,  434,  568,  433
                     ,  569, 1414,  590, 1437,  568, 1435
                     ,  570,  433,  569,  434,  568,  433
                     ,  569, 1411,  593,  436,  567,  433
                     ,  569,  434,  568,  434,  569,  433
                     ,  569,  434,  568,  434,  568, 1437
                     ,  568, 1413,  591, 1410,  595, 1436
                     ,  568
                    };

uint16_t acOFF[] = {  644, 18079, 3047, 9113,  572,  430
                      ,  567, 1412,  593,  435,  566,  435
                      ,  568,  435,  568,  433,  569,  434
                      ,  568,  435,  567,  434,  573, 1432
                      ,  567,  436,  567,  435,  567, 1436
                      ,  569, 1436,  568,  436,  567, 1441
                      ,  563, 1413,  592, 1414,  590, 1411
                      ,  594, 1435,  569,  434,  568,  434
                      ,  569,  434,  567,  435,  568,  435
                      ,  567,  435,  567,  435,  568,  434
                      ,  568,  435,  567,  435,  568,  435
                      ,  572,  429,  568,  411,  591,  435
                      ,  568,  434,  567,  436,  567,  435
                      ,  567,  435,  567,  435,  568,  434
                      ,  568,  435,  572,  429,  568,  411
                      ,  592,  435,  567,  435,  567,  434
                      ,  569,  434,  568,  435,  567,  435
                      ,  567,  435,  568,  435,  572,  429
                      ,  568,  435,  568,  434,  568, 1436
                      ,  569, 1435,  569, 2887, 3073, 9117
                      ,  563, 1412,  592,  410,  593,  434
                      ,  567,  435,  568,  434,  569,  434
                      ,  567,  439,  564,  434,  568,  436
                      ,  566, 1437,  567,  436,  567,  435
                      ,  567, 1413,  592,  434,  568, 1437
                      ,  567, 1413,  592, 1417,  588, 1435
                      ,  569, 1437,  567, 1436,  570,  434
                      ,  568,  434,  567,  435,  568,  434
                      ,  568,  434,  568,  435,  567,  435
                      ,  568,  435,  572,  406,  592,  434
                      ,  568,  434,  568,  435,  567,  436
                      ,  566,  435,  568,  440,  562,  434
                      ,  568,  435,  568,  435,  571,  431
                      ,  567,  435,  567,  434,  568,  435
                      ,  567,  434,  568,  436,  567,  436
                      ,  567,  434,  567,  435,  568,  435
                      ,  572,  430,  567,  436,  566,  435
                      ,  568,  434,  568,  435,  567,  435
                      ,  568,  434,  567,  436,  567, 2913
                      , 3048, 9115,  565, 1435,  569,  435
                      ,  567,  436,  566,  434,  569,  434
                      ,  568,  439,  564,  434,  568,  434
                      ,  568,  434,  568, 1411,  593,  435
                      ,  568,  434,  568,  435,  567,  435
                      ,  568,  438,  564,  434,  568, 1436
                      ,  568, 1413,  592, 1437,  567, 1436
                      ,  569, 1436,  568, 1437,  568, 1436
                      ,  568, 1437,  568, 1436,  568,  440
                      ,  563,  434,  568,  434,  568,  434
                      ,  568,  435,  568,  434,  568,  435
                      ,  567,  436,  567,  434,  568,  435
                      ,  567,  439,  564,  434,  568,  435
                      ,  567,  435,  567, 1435,  569, 1437
                      ,  568, 1436,  569, 1436,  567, 1437
                      ,  567, 1413,  593,  435,  567,  435
                      ,  567,  435,  568,  434,  568,  440
                      ,  561,  437,  567,  435,  567,  435
                      ,  567,  434,  568, 1437,  568, 1436
                      ,  568
                   };

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");

  WebServer.on("/", handleRoot);
  WebServer.on("/ac.cgi", handleONOFF);

  WebServer.begin();
  Serial.println("HTTP Server Started");

  WifiServer.begin();
  WifiServer.setNoDelay(true);

  bool status;
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  OLED.init();
  OLED.flipScreenVertically();

  irsend.begin();
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
      irsend.sendRaw(acON28, sizeof(acON28) / sizeof(acON28[0]), 38);
      AC_state = true;
    }
    else {
      irsend.sendRaw(acOFF, sizeof(acOFF) / sizeof(acOFF[0]), 38);
      AC_state = false;
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
  message += (AC_state ? "ON" : "OFF");

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
      irsend.sendRaw(acON28, sizeof(acON28) / sizeof(acON28[0]), 38);
    }
    else {
      irsend.sendRaw(acOFF, sizeof(acOFF) / sizeof(acOFF[0]), 38);
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

void processWiFiClientResponse(float t, float h, float p) {
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
      if (!AC_state) {
        irsend.sendRaw(acON28, sizeof(acON28) / sizeof(acON28[0]), 38);
        AC_state = true;
        count = 0;
      }
    }
    else {
      count += 1;
    }

  }
  else if (t < 28.0) {
    if (count > 60) {
      if (AC_state) {
        irsend.sendRaw(acOFF, sizeof(acOFF) / sizeof(acOFF[0]), 38);
        AC_state = false;
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

  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure();

  WebServer.handleClient();
  //  airConAutoControl(temperature);

  processWiFiClientResponse(temperature, humidity, pressure);

  Serial.println("Loop End");

  delay(500);

  String degree = "\u00b0";
  String t = "T : " + String(temperature) + degree + "C";

  //  uint16_t width = OLED.getStringWidth(t);

  String percent = "\u0025";
  String h = "H : " + String(humidity) + percent;

  OLED.clear();
  OLED.setFont(ArialMT_Plain_10);
  OLED.drawString(0, 0, "Hellow World");
  OLED.drawFastImage(112, 2, 8, 16, Bat816);

  OLED.setFont(ArialMT_Plain_24);
  OLED.drawString(0, yellowLineOffset, t);
  OLED.drawString(0, yellowLineOffset + blueFontHeigh, h);
  //  OLED.drawXbm(0, yellowLineOffset, temperature_image_width, temperature_image_height, temperature_image_bits);

  OLED.display();

  delay(500);
}

