#ifndef MKL_Gamepad_NRF24_SEAN__
#define MKL_Gamepad_NRF24_SEAN__

#include "Arduino.h"
#include "kxnTask.h"

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

CREATE_TASK(MKL_Gamepad_NRF24)
// CREATE_TASK(GamepadNRF)

public:
RF24 radio_NRF;

MKL_Gamepad_NRF24()
{ // khởi tạo khi gọi hàm
    uint8_t _Pin_CE = 9;
    uint8_t _Pin_CSN = 10;

    byte Address_RF_1[6] = "42912";
    byte Address_RF_2[6] = "28592";
    byte Address_RF_3[6] = "93189";
    byte Address_RF_4[6] = "21659";
    byte Address_RF_5[6] = "94591";
    byte Address_RF_6[6] = "74683";
}
MKL_Gamepad_NRF24(uint8_t Pin_CE, uint8_t Pin_CSN)
{    uint8_t _Pin_CE = 9;
    uint8_t _Pin_CSN = 10;

    byte Address_RF_1[6] = "42912";
    byte Address_RF_2[6] = "28592";
    byte Address_RF_3[6] = "93189";
    byte Address_RF_4[6] = "21659";
    byte Address_RF_5[6] = "94591";
    byte Address_RF_6[6] = "74683";
    radio_NRF.begin(Pin_CE, Pin_CSN);
}

void setup(uint8_t Pin_CE, uint8_t Pin_CSN)
{
}

void setup(uint8_t Pin_CE, uint8_t Pin_CSN, int Address, int SetPAlever, int Setchannel, int SetDataRate)
{
    radio_NRF.begin(Pin_CE, Pin_CSN);
}

END
#endif