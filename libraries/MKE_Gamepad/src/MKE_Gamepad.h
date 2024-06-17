#include "MKE_Gamepad_joystick.h"
#include "MKE_Gamepad_Potential.h"
// #include "MKE_Gamepad_NRF24.h"

#define Pin_Joystick_Ox_Left A0
#define Pin_Joystick_Oy_Left A1
#define Pin_Joystick_Button_Left 1

#define Pin_Joystick_Ox_Right A2
#define Pin_Joystick_Oy_Right A3
#define Pin_Joystick_Button_Right 0

#define Pin_Pot_left A7
#define Pin_Pot_right A6

#define button_1 4
#define button_2 5
#define button_3 6
#define button_4 7

#define button_90D_Left 2
#define button_90D_Right 3

const int buttonPins[8] = {button_1, button_2, button_3, button_4, button_90D_Left, button_90D_Right, Pin_Joystick_Button_Left, Pin_Joystick_Button_Right};

MKE_Gamepad_joystick joystick_L;
MKE_Gamepad_joystick joystick_R;
MKE_Gamepad_Potential Potential_L;
MKE_Gamepad_Potential Potential_R;

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
} Data_MKE_Gamepad;

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
    bitWrite(buttonStates, 0, map(digitalRead(button_1),0,1,1,0));
    bitWrite(buttonStates, 1, map(digitalRead(button_2),0,1,1,0));
    bitWrite(buttonStates, 2, map(digitalRead(button_3),0,1,1,0));
    bitWrite(buttonStates, 3, map(digitalRead(button_4),0,1,1,0));
    bitWrite(buttonStates, 4, map(digitalRead(button_90D_Left),0,1,1,0));
    bitWrite(buttonStates, 5, map(digitalRead(button_90D_Right),0,1,1,0));
    bitWrite(buttonStates, 6, map(digitalRead(Pin_Joystick_Button_Left),0,1,1,0));
    bitWrite(buttonStates, 7, map(digitalRead(Pin_Joystick_Button_Right),0,1,1,0));

    Data_MKE_Gamepad.buttons = buttonStates;
    Data_MKE_Gamepad.DEG_Joy_L = joystick_L.AngleDed();
    Data_MKE_Gamepad.RAD_Joy_L = joystick_L.Radius();
    Data_MKE_Gamepad.DEG_Joy_R = joystick_R.AngleDed();
    Data_MKE_Gamepad.RAD_Joy_R = joystick_R.Radius();
    Data_MKE_Gamepad.pot_L = Potential_L.readValue();
    Data_MKE_Gamepad.pot_R = Potential_R.readValue();

}

void Reset_data_Gamepad() // đưa tất cả giá trị về 0
{
    bitWrite(buttonStates, 0, 1);
    bitWrite(buttonStates, 1, 1);
    bitWrite(buttonStates, 2, 1);
    bitWrite(buttonStates, 3, 1);
    bitWrite(buttonStates, 4, 1);
    bitWrite(buttonStates, 5, 1);
    bitWrite(buttonStates, 6, 1);
    bitWrite(buttonStates, 7, 1);
    Data_MKE_Gamepad.buttons = buttonStates;

    Data_MKE_Gamepad.DEG_Joy_L = 0;
    Data_MKE_Gamepad.RAD_Joy_L = 0;
    Data_MKE_Gamepad.DEG_Joy_R = 0;
    Data_MKE_Gamepad.RAD_Joy_R = 0;
    Data_MKE_Gamepad.pot_L = 0;
    Data_MKE_Gamepad.pot_R = 0;

    // Serial.println( Potential_R.readValue());
}

int Get_POT_L() { return Data_MKE_Gamepad.pot_L; }
int Get_POT_R() { return Data_MKE_Gamepad.pot_R; }
int Get_DEG_Joy_L() { return Data_MKE_Gamepad.DEG_Joy_L; }
int Get_DEG_Joy_R() { return Data_MKE_Gamepad.DEG_Joy_R; }
int Get_RAD_Joy_L() { return Data_MKE_Gamepad.RAD_Joy_L; }
int Get_RAD_Joy_R() { return Data_MKE_Gamepad.RAD_Joy_R; }
bool Get_status_button_2() { return bitRead(buttonStates, 1); }
bool Get_status_button_3() { return bitRead(buttonStates, 2); }
bool Get_status_button_1() { return bitRead(buttonStates, 0); }
bool Get_status_button_4() { return bitRead(buttonStates, 3); }
bool Get_status_button_90D_Left() { return bitRead(buttonStates, 4); }
bool Get_status_button_90D_Right() { return bitRead(buttonStates, 5); }
bool Get_status_Joystick_Button_Left() { return bitRead(buttonStates, 6); }
bool Get_status_Joystick_Button_Right() { return bitRead(buttonStates, 7); }
