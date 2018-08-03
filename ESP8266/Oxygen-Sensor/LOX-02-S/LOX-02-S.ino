#include "SSD1306.h"
SSD1306 OLED(0x3D, 4, 5);
boolean oledState = false;

const uint8_t POLL_MODE[] = {0x4D, 0x20, 0x31, 0x0D, 0x0A};
const uint8_t STREAM_MODE[] = {0x4D, 0x20, 0x32, 0x0D, 0x0A};
const uint8_t STOP_MODE[] = {0x4D, 0x20, 0x33, 0x0D, 0x0A};

const uint8_t REQ_O2[] = {0x25, 0x0D, 0x0A};

void setup() {
  // put your setup code here, to run once:
  oledState = OLED.init();
  if ( !oledState ) {
    Serial.println("Could not find a valid OLED, check wiring!");
  }

  //  OLED.flipScreenVertically();

  OLED.clear();
  OLED.setFont(ArialMT_Plain_24);
  OLED.drawString(0, 0, "CONTROL");
  OLED.display();

  Serial.begin(9600);

  char *str = strtok("a b c", " ");
  Serial.println(str);

  str = strtok(NULL, " ");
  Serial.println(str);

  while (!Serial) {
    ;
  }
  //  Serial.write("M");
  //  Serial.println(1, HEX);

  Serial.write(STREAM_MODE, sizeof(STREAM_MODE) / sizeof(STREAM_MODE[0]));
  delay(100);

  //  String value = Serial.readStringUntil('\n');
  //  char tmp[100];
  //  value.toCharArray(tmp, 100);
  //
  //  char *O = strtok(tmp, " ");
  //  char *O_value = (NULL, " ");
}

void loop() {
  // put your main code here, to run repeatedly:

  if (Serial.available() > 0) {
    //    Serial.write(REQ_O2, sizeof(REQ_O2) / sizeof(REQ_O2[0]));
    String value = Serial.readStringUntil('\n');
    delay(100);

    if ( value.length() == 40 ) {
      String O = value.substring(2, 8);
      String T = value.substring(11, 16);
      String P = value.substring(19, 23);
      String X = value.substring(26, 32);
      String e = value.substring(35, 39);

      OLED.clear();
      OLED.setFont(ArialMT_Plain_10);
      OLED.drawString(0, 0, O);
      OLED.drawString(0, 10, T);
      OLED.drawString(0, 20, P);
      OLED.drawString(0, 30, X);
      OLED.drawString(0, 40, e);
      OLED.drawString(0, 50, value);

      OLED.display();
    }



    delay(100);
    //    Serial1.println(inByte);

  }

}
