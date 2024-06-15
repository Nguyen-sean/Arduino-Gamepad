#include "MKE_Gamepad_joystick.h"
#include "MKE_Gamepad_Potential.h"
// #include "MKE_Gamepad_NRF24.h"

#define Pin_Joystick_Ox_Left A0  
#define Pin_Joystick_Oy_Left A1
#define Pin_Joystick_Button_Left 0

#define Pin_Joystick_Ox_Right A2  
#define Pin_Joystick_Oy_Right A3
#define Pin_Joystick_Button_Right 1

#define Pin_Pot_left A7
#define Pin_Pot_right A6

#define button_1 
#define button_2
#define button_3
#define button_4

#define button_90D_Left
#define button_90D_Right

MKE_Gamepad_joystick joystick_L;
MKE_Gamepad_joystick joystick_R;
MKE_Gamepad_Potential Potential_L;
MKE_Gamepad_Potential Potential_R;

struct DataPacket
{
    byte buttons;
    int DEG_Joy_L;
    int RAD_Joy_L;
    int RAD_Joy_R;
    int DEG_Joy_R;
    int pot_L;
    int pot_R;
} data;

void Setup_Gamepad()
{
    joystick_L.setup(Pin_Joystick_Ox_Left, Pin_Joystick_Oy_Left, Pin_Joystick_Button_Left);
    joystick_R.setup(Pin_Joystick_Ox_Right, Pin_Joystick_Oy_Right, Pin_Joystick_Button_Right);
    Potential_L.setup(Pin_Pot_left);
    Potential_R.setup(Pin_Pot_right);
}

void getdata_Gamepad(){

}