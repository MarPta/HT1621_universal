#ifndef _HT1621_UNIVERSAL_
#define _HT1621_UNIVERSAL_

#include <Arduino.h>

class HT1621_universal {
    uint8_t csPin, wrPin, dataPin;

    static const uint8_t ComMode = 0x52;
    static const uint8_t RCosc = 0x30;
    static const uint8_t LCD_on = 0x06;
    static const uint8_t LCD_off = 0x04;
    static const uint8_t Sys_en = 0x02;
    static const uint8_t CTRl_cmd = 0x80;
    static const uint8_t Data_cmd = 0xa0;

    static const uint8_t delayUs = 1;

public:
    static const uint8_t num[];
    uint8_t dispnum[6]={0x00,0x00,0x00,0x00,0x00,0x00};

    inline uint8_t sbi(uint8_t * x, uint8_t y);
    inline uint8_t cbi(uint8_t * x, uint8_t y);
    void SendBit_1621(uint8_t sdata, uint8_t cnt);
    void SendCmd_1621(uint8_t command);
    void Write_1621(uint8_t addr, uint8_t sdata);
    void HT1621_all_off(uint8_t num);
    void HT1621_all_on(uint8_t num);
    void init(void);
    void displaydata(int p);
    void displayCelsius(float temperature);

    HT1621_universal(uint8_t csPin, uint8_t wrPin, uint8_t dataPin);
};

#endif //_HT1621_UNIVERSAL_