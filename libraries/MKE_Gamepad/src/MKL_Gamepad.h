#ifndef MKL_Gamepad_SEAN__
#define MKL_Gamepad_SEAN__

#include "kxnTask.h"

#include <Wire.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// #ifdef AVR

#include "MKL_Gamepad_joystick.h"
#include "MKL_Gamepad_Potential.h"

MKL_Gamepad_joystick joystick_L;
MKL_Gamepad_joystick joystick_R;
MKL_Gamepad_Potential Potential_L;
MKL_Gamepad_Potential Potential_R;

// #endif
// #include "MKL_Gamepad_NRF24.h"

// DEFINE_TASK_STATE(MKL_Gamepad){
//     Gamepad_Setting,
//     Gamepad_ON,
//     Gamepad_OFF};

// default
#define Default_Pin_CE 9
#define Default_Pin_CSN 10
// uint8_t I2C_ADDRESS = 0x6C; // I2C address
uint8_t I2C_ADDRESS = 0x08;

CREATE_TASK(MKL_Gamepad)

/*
###########################################################
-------------------Config_Pinout_Gamepad-------------------
###########################################################
*/

byte buttonStates = 0;
struct DataPacket
{
    byte buttons;
    int DEG_Joy_L;
    int RAD_Joy_L;
    int RAD_Joy_R;
    int DEG_Joy_R;
    int pot_L;
    int pot_R;
    // bool Is_connect_NRF;
} Data_MKL_Gamepad_push;

/*
###########################################################
-------------------Config_Pinout_Gamepad-------------------
###########################################################
*/
#ifdef AVR
uint8_t Pin_Joystick_Ox_Left = A0;
uint8_t Pin_Joystick_Oy_Left = A1;
// uint8_t Pin_Joystick_Ox_Left = 2;
// uint8_t Pin_Joystick_Oy_Left = 2;
uint8_t Pin_Joystick_Button_Left = 1;

uint8_t Pin_Joystick_Ox_Right = A2;
uint8_t Pin_Joystick_Oy_Right = A3;
// uint8_t Pin_Joystick_Ox_Right = 2;
// uint8_t Pin_Joystick_Oy_Right = 3;
uint8_t Pin_Joystick_Button_Right = 0;

uint8_t Pin_Pot_left = A7;
uint8_t Pin_Pot_right = A6;
// uint8_t Pin_Pot_left = 7;
// uint8_t Pin_Pot_right = 6;

uint8_t button_1 = 4;
uint8_t button_2 = 5;
uint8_t button_3 = 6;
uint8_t button_4 = 7;

uint8_t button_90D_Left = 2;
uint8_t button_90D_Right = 3;

//
void SET_Pin_Joystick_Ox_Left(uint8_t _pin_Input) { this->Pin_Joystick_Ox_Left = _pin_Input; }
void SET_Pin_Joystick_Oy_Left(uint8_t _pin_Input) { this->Pin_Joystick_Oy_Left = _pin_Input; }
void SET_Pin_Joystick_Button_Left(uint8_t _pin_Input) { this->Pin_Joystick_Button_Left = _pin_Input; }
void SET_Pin_Joystick_Ox_Right(uint8_t _pin_Input) { this->Pin_Joystick_Ox_Right = _pin_Input; }
void SET_Pin_Joystick_Oy_Right(uint8_t _pin_Input) { this->Pin_Joystick_Oy_Right = _pin_Input; }
void SET_Pin_Joystick_Button_Right(uint8_t _pin_Input) { this->Pin_Joystick_Button_Right = _pin_Input; }
void SET_Pin_Pot_left(uint8_t _pin_Input) { this->Pin_Pot_left = _pin_Input; }
void SET_Pin_Pot_right(uint8_t _pin_Input) { this->Pin_Pot_right = _pin_Input; }
void SET_button_1(uint8_t _pin_Input) { this->button_1 = _pin_Input; }
void SET_button_2(uint8_t _pin_Input) { this->button_2 = _pin_Input; }
void SET_button_3(uint8_t _pin_Input) { this->button_3 = _pin_Input; }
void SET_button_4(uint8_t _pin_Input) { this->button_4 = _pin_Input; }
void SET_button_90D_Left(uint8_t _pin_Input) { this->button_90D_Left = _pin_Input; }
void SET_button_90D_Right(uint8_t _pin_Input) { this->button_90D_Right = _pin_Input; }

//----------------------------------------
const int buttonPins[8] = {button_1, button_2, button_3, button_4, button_90D_Left, button_90D_Right, Pin_Joystick_Button_Left, Pin_Joystick_Button_Right};


//----------------------------------------------------------

void Setup_Gamepad()
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }

    joystick_L.setup(Pin_Joystick_Ox_Left, Pin_Joystick_Oy_Left, Pin_Joystick_Button_Left);
    joystick_R.setup(Pin_Joystick_Ox_Right, Pin_Joystick_Oy_Right, Pin_Joystick_Button_Right);
    Potential_L.setup(Pin_Pot_left);
    Potential_R.setup(Pin_Pot_right);
}

void getdata_Gamepad()
{
    bitWrite(buttonStates, 0, digitalRead(button_1));
    bitWrite(buttonStates, 1, digitalRead(button_2));
    bitWrite(buttonStates, 2, digitalRead(button_3));
    bitWrite(buttonStates, 3, digitalRead(button_4));
    bitWrite(buttonStates, 4, digitalRead(button_90D_Left));
    bitWrite(buttonStates, 5, digitalRead(button_90D_Right));
    bitWrite(buttonStates, 6, digitalRead(Pin_Joystick_Button_Left));
    bitWrite(buttonStates, 7, digitalRead(Pin_Joystick_Button_Right));

    Data_MKL_Gamepad_push.buttons = buttonStates;
    Data_MKL_Gamepad_push.DEG_Joy_L = joystick_L.AngleDed();
    Data_MKL_Gamepad_push.RAD_Joy_L = joystick_L.Radius();
    Data_MKL_Gamepad_push.DEG_Joy_R = joystick_R.AngleDed();
    Data_MKL_Gamepad_push.RAD_Joy_R = joystick_R.Radius();
    Data_MKL_Gamepad_push.pot_L = Potential_L.readValue();
    Data_MKL_Gamepad_push.pot_R = Potential_R.readValue();
}
#endif
void Reset_data_Gamepad() // đưa tất cả giá trị về low
{
    bitWrite(buttonStates, 0, 1);
    bitWrite(buttonStates, 1, 1);
    bitWrite(buttonStates, 2, 1);
    bitWrite(buttonStates, 3, 1);
    bitWrite(buttonStates, 4, 1);
    bitWrite(buttonStates, 5, 1);
    bitWrite(buttonStates, 6, 1);
    bitWrite(buttonStates, 7, 1);
    Data_MKL_Gamepad_push.buttons = buttonStates;

    Data_MKL_Gamepad_push.DEG_Joy_L = 0;
    Data_MKL_Gamepad_push.RAD_Joy_L = 0;
    Data_MKL_Gamepad_push.DEG_Joy_R = 0;
    Data_MKL_Gamepad_push.RAD_Joy_R = 0;
    Data_MKL_Gamepad_push.pot_L = 0;
    Data_MKL_Gamepad_push.pot_R = 0;

    // Serial.println( Potential_R.readValue());
}

int Get_POT_L() { return Data_MKL_Gamepad_push.pot_L; }
int Get_POT_R() { return Data_MKL_Gamepad_push.pot_R; }
int Get_DEG_Joy_L() { return Data_MKL_Gamepad_push.DEG_Joy_L; }
int Get_DEG_Joy_R() { return Data_MKL_Gamepad_push.DEG_Joy_R; }
int Get_RAD_Joy_L() { return Data_MKL_Gamepad_push.RAD_Joy_L; }
int Get_RAD_Joy_R() { return Data_MKL_Gamepad_push.RAD_Joy_R; }
bool Get_status_button_1() { return !bitRead(Data_MKL_Gamepad_push.buttons, 0); }
bool Get_status_button_2() { return !bitRead(Data_MKL_Gamepad_push.buttons, 1); }
bool Get_status_button_3() { return !bitRead(Data_MKL_Gamepad_push.buttons, 2); }
bool Get_status_button_4() { return !bitRead(Data_MKL_Gamepad_push.buttons, 3); }
bool Get_status_button_90D_Left() { return !bitRead(Data_MKL_Gamepad_push.buttons, 4); }
bool Get_status_button_90D_Right() { return !bitRead(Data_MKL_Gamepad_push.buttons, 5); }
bool Get_status_Joystick_Button_Left() { return !bitRead(Data_MKL_Gamepad_push.buttons, 6); }
bool Get_status_Joystick_Button_Right() { return !bitRead(Data_MKL_Gamepad_push.buttons, 7); }

void getdata_Gamepad_I2C()
{
    Wire.requestFrom(I2C_ADDRESS, sizeof(Data_MKL_Gamepad_push));
    while (Wire.available())
    { // slave may send less than requested
        Wire.readBytes((char *)&Data_MKL_Gamepad_push, sizeof(Data_MKL_Gamepad_push));
    }
}

// void senddata_gamepad_I2C()
// {
//     Wire.begin(I2C_ADDRESS); // join I2C bus with address #8
//     Wire.onRequest(requestEvent);
// }

END

#endif