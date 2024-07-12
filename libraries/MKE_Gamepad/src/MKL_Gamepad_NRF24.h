#ifndef MKL_Gamepad_NRF24_SEAN__
#define MKL_Gamepad_NRF24_SEAN__

#include "Arduino.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

class MKL_Gamepad_NRF24
{

private:
    uint8_t Pin_CE;
    uint8_t Pin_CSN;
    byte Address_RF_1[6] = "42912";
    byte Address_RF_2[6] = "28592";
    byte Address_RF_3[6] = "93189";
    byte Address_RF_4[6] = "21659";
    byte Address_RF_5[6] = "94591";
    byte Address_RF_6[6] = "74683";

public:
    void RF_writing();
    void Change_address_RF();
    void Config_NRF(uint8_t CE, uint8_t CSN, int Address, int SetPAlever, int Setchannel, int SetDataRate)
    {
        RF24 radio(9, 10);
    }
    // void Se
};

#endif