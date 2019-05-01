#include <Arduino.h>
#include "HT1621_universal.h"

const uint8_t csPin = 14;   //Chip selection output
const uint8_t wrPin = 27;   //Read clock output
const uint8_t dataPin = 26; //Serial data output

HT1621_universal lcd(csPin, wrPin, dataPin);

void setup() {
    lcd.init();
    lcd.HT1621_all_on(16);
    delay(1000);
    lcd.Write_1621(0,lcd.num[0]);  //0
    lcd.Write_1621(2,lcd.num[1]);  //1
    lcd.Write_1621(4,lcd.num[2]);  //2
    lcd.Write_1621(6,lcd.num[3]);  //3
    lcd.Write_1621(8,lcd.num[4]);  //4
    lcd.Write_1621(10,lcd.num[5]); //5
    delay(1000);
    lcd.HT1621_all_off(10);
    delay(1000);

    Serial.begin(115200);
}
 
void loop() {
    lcd.displayCelsius(18.3);
    delay(2000);
}