#include "MKE_Gamepad_joystick.h"

MKE_Gamepad_joystick MKE_Gamepad_joystick_1;
MKE_Gamepad_joystick MKE_Gamepad_joystick_2;

void setup() {
  Serial.begin(115200);

  MKE_Gamepad_joystick_1.setup(A0, A1, 2);
  MKE_Gamepad_joystick_2.setup(A2, A3, 3);
  // put your setup code here, to run once:

}

void loop() {

  // Serial.print(MKE_Gamepad_joystick_1.Radius_approximately(10));
  // Serial.print("  ||  ");
  //  Serial.println(MKE_Gamepad_joystick_2.Radius_approximately(10));
  MKE_Gamepad_joystick_2.Serial_debug();
  // put your main code here, to run repeatedly:

}
