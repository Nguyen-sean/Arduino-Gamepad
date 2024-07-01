#include "MKL_Gamepad.h"

MKL_Gamepad_joystick joystick_L;
MKL_Gamepad_joystick joystick_R;
MKL_Gamepad_Potential Potential_L;
MKL_Gamepad_Potential Potential_R;

void setup()
{
  Serial.begin(115200);

  joystick_L.setup(A0, A1, 2);
  joystick_R.setup(A2, A3, 3);
  Potential_L.setup(A7);
  Potential_R.setup(A6);
  // put your setup code here, to run once:
}

void loop()
{

  // Serial.print(MKL_Gamepad_joystick_L.Radius());
  // Serial.print("  ||  ");
  // Serial.print(MKL_Gamepad_joystick_R.Radius());
  // MKL_Gamepad_joystick_R.Serial_debug();

  Serial.print(joystick_L.AngleDed());
  Serial.print("  ||  ");
  Serial.print(joystick_R.AngleDed());
  Serial.print("  ||  ");
  Serial.print(Potential_L.readValue());
  Serial.print("  ||  ");
  Serial.println(Potential_R.readValue());
  // put your main code here, to run repeatedly:
}
