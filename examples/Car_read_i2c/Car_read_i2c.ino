// Gamepad.Get_POT_R() 
// Gamepad.Get_DEG_Joy_L() 
// Gamepad.Get_DEG_Joy_R() 
// Gamepad.Get_POT_L() 
// Gamepad.Get_RAD_Joy_L() 
// Gamepad.Get_RAD_Joy_R() 
// Gamepad.Get_status_button_1()
// Gamepad.Get_status_button_2()
// Gamepad.Get_status_button_3()
// Gamepad.Get_status_button_4()
// Gamepad.Get_status_button_90D_Left()
// Gamepad.Get_status_button_90D_Right()
// Gamepad.Get_status_Joystick_Button_Left() 
// Gamepad.Get_status_Joystick_Button_Right() 
#include "MKL_Gamepad.h"

MKL_Gamepad Gamepad;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
}


void loop() {

  Gamepad.getdata_Gamepad_I2C();

  Serial.println(Gamepad.Get_RAD_Joy_L());
}
