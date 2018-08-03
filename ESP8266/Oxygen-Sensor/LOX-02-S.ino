#include "SSD1306.h"
SSD1306 OLED(0x3D, 4, 5);
boolean oledState = false;

const uint8_t POLL_MODE[] = {0x4D, 0x20, 0x31, 0x0D, 0x0A};
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

    Serial.write(POLL_MODE, sizeof(POLL_MODE) / sizeof(POLL_MODE[0]));
    delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  
//      if (Serial.available() > 0) {
//        //    String value = Serial.readStringUntil('\n');
//  
//        Serial.write(REQ_O2, sizeof(REQ_O2) / sizeof(REQ_O2[0]));
//        delay(500);
//        String value = Serial.readStringUntil('\n');
//        delay(500);
//        OLED.clear();
//        OLED.setFont(ArialMT_Plain_10);
//        OLED.drawString(0, 0, value);
//        OLED.display();
//  
//        delay(100);
//        //    Serial1.println(inByte);
//  
//      }

}
