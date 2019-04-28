#ifndef _HT1621_UNIVERSAL_
#define _HT1621_UNIVERSAL_

#include <Arduino.h>

class HT1621_universal {
    uint8_t csPin, wrPin, dataPin;
public:
    HT1621_universal(uint8_t csPin, uint8_t wrPin, uint8_t dataPin):csPin(csPin), wrPin(wrPin), dataPin(dataPin) {

    }
};



#endif //_HT1621_UNIVERSAL_