#ifndef MKL_Gamepad_SEAN__
#define MKL_Gamepad_SEAN__

#include <Wire.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "MKL_Gamepad_joystick.h"
#include "MKL_Gamepad_Potential.h"
#include "MKL_Gamepad_NRF24.h"


//default 
#define Default_Pin_CE 9
#define Default_Pin_CSN 10
uint8_t I2C_ADDRESS = 0x6C; // I2C address 

class MKL_Gamepad
{
private:
    
    uint8_t Pin_Joystick_Ox_Left = A0;
    uint8_t Pin_Joystick_Oy_Left = A1;
    uint8_t Pin_Joystick_Button_Left = 1;

    uint8_t Pin_Joystick_Ox_Right = A2;
    uint8_t Pin_Joystick_Oy_Right = A3;
    uint8_t Pin_Joystick_Button_Right = 0;

    uint8_t Pin_Pot_left = A7;
    uint8_t Pin_Pot_right = A6;

    uint8_t button_1 = 4;
    uint8_t button_2 = 5;
    uint8_t button_3 = 6;
    uint8_t button_4 = 7;

    uint8_t button_90D_Left = 2;
    uint8_t button_90D_Right = 3;

    const int buttonPins[8] = {button_1, button_2, button_3, button_4, button_90D_Left, button_90D_Right, Pin_Joystick_Button_Left, Pin_Joystick_Button_Right};

    MKL_Gamepad_joystick joystick_L;
    MKL_Gamepad_joystick joystick_R;
    MKL_Gamepad_Potential Potential_L;
    MKL_Gamepad_Potential Potential_R;

public:
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
    } Data_MKL_Gamepad;

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

        Data_MKL_Gamepad.buttons = buttonStates;
        Data_MKL_Gamepad.DEG_Joy_L = joystick_L.AngleDed();
        Data_MKL_Gamepad.RAD_Joy_L = joystick_L.Radius();
        Data_MKL_Gamepad.DEG_Joy_R = joystick_R.AngleDed();
        Data_MKL_Gamepad.RAD_Joy_R = joystick_R.Radius();
        Data_MKL_Gamepad.pot_L = Potential_L.readValue();
        Data_MKL_Gamepad.pot_R = Potential_R.readValue();
    }

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
        Data_MKL_Gamepad.buttons = buttonStates;

        Data_MKL_Gamepad.DEG_Joy_L = 0;
        Data_MKL_Gamepad.RAD_Joy_L = 0;
        Data_MKL_Gamepad.DEG_Joy_R = 0;
        Data_MKL_Gamepad.RAD_Joy_R = 0;
        Data_MKL_Gamepad.pot_L = 0;
        Data_MKL_Gamepad.pot_R = 0;

        // Serial.println( Potential_R.readValue());
    }

    int Get_POT_L() { return Data_MKL_Gamepad.pot_L; }
    int Get_POT_R() { return Data_MKL_Gamepad.pot_R; }
    int Get_DEG_Joy_L() { return Data_MKL_Gamepad.DEG_Joy_L; }
    int Get_DEG_Joy_R() { return Data_MKL_Gamepad.DEG_Joy_R; }
    int Get_RAD_Joy_L() { return Data_MKL_Gamepad.RAD_Joy_L; }
    int Get_RAD_Joy_R() { return Data_MKL_Gamepad.RAD_Joy_R; }
    bool Get_status_button_1() { return !bitRead(Data_MKL_Gamepad.buttons, 0); }
    bool Get_status_button_2() { return !bitRead(Data_MKL_Gamepad.buttons, 1); }
    bool Get_status_button_3() { return !bitRead(Data_MKL_Gamepad.buttons, 2); }
    bool Get_status_button_4() { return !bitRead(Data_MKL_Gamepad.buttons, 3); }
    bool Get_status_button_90D_Left() { return !bitRead(Data_MKL_Gamepad.buttons, 4); }
    bool Get_status_button_90D_Right() { return !bitRead(Data_MKL_Gamepad.buttons, 5); }
    bool Get_status_Joystick_Button_Left() { return !bitRead(Data_MKL_Gamepad.buttons, 6); }
    bool Get_status_Joystick_Button_Right() { return !bitRead(Data_MKL_Gamepad.buttons, 7); }

    void getdata_Gamepad_I2C()
    {
        Wire.requestFrom(I2C_ADDRESS, sizeof(Data_MKL_Gamepad));
        while (Wire.available())
        { // slave may send less than requested
            Wire.readBytes((char *)&Data_MKL_Gamepad, sizeof(Data_MKL_Gamepad));
        }
    }

    // void senddata_gamepad_I2C()
    // {
    //     Wire.begin(I2C_ADDRESS); // join I2C bus with address #8
    //     Wire.onRequest(requestEvent);
    // }
};

#endif