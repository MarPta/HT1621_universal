#include <Arduino.h>
#include "HT1621_universal.h"

const uint8_t csPin = 14;   //Chip selection output
const uint8_t wrPin = 27;   //Read clock output
const uint8_t dataPin = 26; //Serial data output

const uint8_t ComMode = 0x52;
const uint8_t RCosc = 0x30;
const uint8_t LCD_on = 0x06;
const uint8_t LCD_off = 0x04;
const uint8_t Sys_en = 0x02;
const uint8_t CTRl_cmd = 0x80;
const uint8_t Data_cmd = 0xa0;

const uint8_t delayUs = 1;

HT1621_universal lcd(csPin, wrPin, dataPin);

/* 0,1,2,3,4,5,6,7,8,9,A,b,C,c,d,E,F,H,h,L,n,N,o,P,r,t,U,-, ,° */
const char num[]={0x7D,0x60,0x3E,0x7A,0x63,0x5B,0x5F,0x70,0x7F,0x7B,0x77,0x4F,0x1D,0x0E,0x6E,0x1F,0x17,0x67,0x47,0x0D,0x46,0x75,0x37,0x06,0x0F,0x6D,0x02,0x00,0x33};
char dispnum[6]={0x00,0x00,0x00,0x00,0x00,0x00};

inline uint8_t sbi(uint8_t x, uint8_t y) {
    return x |= (1 << y);
}

inline uint8_t cbi(uint8_t x, uint8_t y) {
    return x |= (1 << y);
}

void SendBit_1621(uint8_t sdata, uint8_t cnt) {
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

void SendCmd_1621(uint8_t command) {
    digitalWrite(csPin, LOW);
    SendBit_1621(0x80,4);
    SendBit_1621(command,8);
    digitalWrite(csPin, HIGH);
}

void Write_1621(uint8_t addr, uint8_t sdata) {
    addr<<=2;
    digitalWrite(csPin, LOW);
    SendBit_1621(0xa0,3);
    SendBit_1621(addr,6);
    SendBit_1621(sdata,8);
    digitalWrite(csPin, HIGH);
}

void HT1621_all_off(uint8_t num) {
    uint8_t i;
    uint8_t addr=0;
    for(i=0;i<num;i++)
    {
        Write_1621(addr,0x00);
        addr+=2;
    }
}

void HT1621_all_on(uint8_t num) {
    uint8_t i;
    uint8_t addr=0;
    for(i=0;i<num;i++)
    {
        Write_1621(addr,0xff);
        addr+=2;
    }
}

void Init_1621(void) {
    SendCmd_1621(Sys_en);
    SendCmd_1621(RCosc);
    SendCmd_1621(ComMode);
    SendCmd_1621(LCD_on);
}

void displaydata(int p)
{
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

void setup() {
    pinMode(csPin, OUTPUT);
    pinMode(wrPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    digitalWrite(csPin, HIGH);
    digitalWrite(dataPin, HIGH);
    digitalWrite(wrPin, HIGH);
    delay(50);
    Init_1621();
    HT1621_all_on(16);
    delay(1000);
    HT1621_all_off(16);
    delay(1000);
    
    displaydata(1);//light on the first decimal point starting from the right side
    delay(1000);
    dispnum[5]=num[5];
    dispnum[4]=num[4];
    dispnum[3]=num[3];
    dispnum[2]=num[2];
    dispnum[1]=num[1];
    dispnum[0]=num[0];
    
    sbi(dispnum[5],7);
    //cbi(dispnum[5],7);
    sbi(dispnum[4],7);
    //cbi(dispnum[4],7);
    sbi(dispnum[3],7);
    //cbi(dispnum[3],7);
    
    delay(1000);
    
    Write_1621(0,num[0]);  //0
    Write_1621(2,num[1]);  //1
    Write_1621(4,num[2]);  //2
    Write_1621(6,num[3]);  //3
    Write_1621(8,num[4]);  //4
    Write_1621(10,num[5]); //5
    delay(1000);
    HT1621_all_off(10);
    delay(1000);

    Serial.begin(115200);
}
 
void loop() {
    HT1621_all_off(10);

    Write_1621(0,num[5]);
    Write_1621(2,num[4]);
    Write_1621(6,num[3]);
    Write_1621(8,num[2]);

    for (int i=0; i <= 4; i++) {
    Write_1621(4,num[26]);  // -
    delay(1000);
    Write_1621(4,num[27]);  // empty space
    delay(1000);
    } 
    
    HT1621_all_off(16);
    delay(1000);
    
    Write_1621(6,num[1]);
    Write_1621(4,num[7]);
    Write_1621(2,num[28]);  // degree
    Write_1621(0,num[12]);  // C
    delay(2000);
    Serial.println(F_CPU);
}