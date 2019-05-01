#include "HT1621_universal.h"

/* 0,1,2,3,4,5,6,7,8,9,A,b,C,c,d,E,F,H,h,L,n,N,o,P,r,t,U,-, ,° */
const uint8_t HT1621_universal::num[] = {
    0x7D, 0x60, //0, 1
    0x3E, 0x7A, //2, 3
    0x63, 0x5B, //4, 5
    0x5F, 0x70, //6, 7
    0x7F, 0x7B, //8, 9
    0x77, 0x4F, //A, b
    0x1D, 0x0E, //C, c
    0x6E, 0x1F, //d, E
    0x17, 0x67, //F, H
    0x47, 0x0D, //h, L
    0x46, 0x75, //n, N
    0x37, 0x06, //P, r
    0x0F, 0x6D, //t, U
    0x02, 0x00, //-, " "
    0x33};      //°

HT1621_universal::HT1621_universal(uint8_t csPin, uint8_t wrPin, uint8_t dataPin):csPin(csPin), wrPin(wrPin), dataPin(dataPin) {
}

inline uint8_t HT1621_universal::sbi(uint8_t x, uint8_t y) {
    return x |= (1 << y);
}

inline uint8_t HT1621_universal::cbi(uint8_t x, uint8_t y) {
    return x |= (1 << y);
}

void HT1621_universal::SendBit_1621(uint8_t sdata, uint8_t cnt) {
    uint8_t i;
    for(i=0;i<cnt;i++) {
        digitalWrite(wrPin, LOW);
        delayMicroseconds(delayUs);
        if(sdata&0x80) digitalWrite(dataPin, HIGH);
        else digitalWrite(dataPin, LOW);
        digitalWrite(wrPin, HIGH) ;
        delayMicroseconds(delayUs);
        sdata<<=1;
    } 
}

void HT1621_universal::SendCmd_1621(uint8_t command) {
    digitalWrite(csPin, LOW);
    SendBit_1621(0x80,4);
    SendBit_1621(command,8);
    digitalWrite(csPin, HIGH);
}

void HT1621_universal::Write_1621(uint8_t addr, uint8_t sdata) {
    addr<<=2;
    digitalWrite(csPin, LOW);
    SendBit_1621(0xa0,3);
    SendBit_1621(addr,6);
    SendBit_1621(sdata,8);
    digitalWrite(csPin, HIGH);
}

void HT1621_universal::HT1621_all_off(uint8_t num) {
    uint8_t i;
    uint8_t addr=0;
    for(i=0;i<num;i++)
    {
        Write_1621(addr,0x00);
        addr+=2;
    }
}

void HT1621_universal::HT1621_all_on(uint8_t num) {
    uint8_t i;
    uint8_t addr=0;
    for(i=0;i<num;i++)
    {
        Write_1621(addr,0xff);
        addr+=2;
    }
}

void HT1621_universal::init(void) {
    pinMode(csPin, OUTPUT);
    pinMode(wrPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    digitalWrite(csPin, HIGH);
    digitalWrite(dataPin, HIGH);
    digitalWrite(wrPin, HIGH);

    delay(50);

    SendCmd_1621(Sys_en);
    SendCmd_1621(RCosc);
    SendCmd_1621(ComMode);
    SendCmd_1621(LCD_on);
}

void HT1621_universal::displaydata(int p) {
    uint8_t i=0;
    switch(p) {
        case 1:
        sbi(dispnum[0], 7);
        break;
        case 2:
        sbi(dispnum[1], 7);
        break;
        case 3:
        sbi(dispnum[2], 7);
        break;
        default:break;
    }
    for(i = 0; i <= 5; i++) {
        Write_1621(i*2, dispnum[i]);
    }
}