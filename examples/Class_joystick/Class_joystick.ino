#include "MKE_Gamepad.h"


MKE_Gamepad_joystick joystick_L;
MKE_Gamepad_joystick joystick_R;
MKE_Gamepad_Potential Potential_L;
MKE_Gamepad_Potential Potential_R;


void setup() {
  Serial.begin(115200);

joystick_L.setup(A0, A1, 2);
joystick_R.setup(A2, A3, 3);
Potential_L.setup(A7);
Potential_R.setup(A6);
  // put your setup code here, to run once:
}

void loop() {

  // Serial.print(MKE_Gamepad_joystick_L.Radius());
  // Serial.print("  ||  ");
  // Serial.print(MKE_Gamepad_joystick_R.Radius());
  // MKE_Gamepad_joystick_R.Serial_debug();

  Serial.print(joystick_L.Radius());
  Serial.print("  ||  ");
  Serial.print(joystick_R.Radius());
  Serial.print("  ||  ");
  Serial.print(Potential_L.readValue());
  Serial.print("  ||  ");
  Serial.println(Potential_R.readValue());
  // put your main code here, to run repeatedly:
}
