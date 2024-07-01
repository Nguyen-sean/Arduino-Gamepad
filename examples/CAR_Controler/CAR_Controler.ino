#include "MKL_Gamepad.h"
#include <Wire.h>

MKL_Gamepad Gamepad;

void forward();
void back();
void left();
void right();
void forwardleft();
void forwardright();
void backright();
void backleft();
void Stop();

#define in1 9 // L298n Motor Driver pins.
#define in2 8
#define in3 7
#define in4 4

#define LED 13

#define pwm_1 6 // Speed motor
#define pwm_2 5

int command;
float DEG_joystick;
int Speed = 150;

char servo_compare = 'B';
char servo_compare_s = 'A';
void setup()
{
  Wire.begin(); // join I2C bus (address optional for master)
  Serial.begin(115200);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LED, OUTPUT); // Set the LED pin.

  pinMode(pwm_1, OUTPUT);
  pinMode(pwm_2, OUTPUT);

  analogWrite(pwm_1, Speed);
  analogWrite(pwm_2, Speed);
}

void loop()
{
  // Wire.requestFrom(8, sizeof(Gamepad.Data_MKL_Gamepad));
  // while (Wire.available())
  // { // slave may send less than requested
  //   Wire.readBytes((char *)&Gamepad.Data_MKL_Gamepad, sizeof(Gamepad.Data_MKL_Gamepad));
  //   // Serial.print(Gamepad.Get_DEG_Joy_L());
  //   // Serial.print(" || ");
  //   // Serial.print(Gamepad.Get_RAD_Joy_L());
  //   // Serial.print(" ||<==>|| ");
  //   // Serial.print(Gamepad.Get_DEG_Joy_R());
  //   // Serial.print(" || ");
  //   // Serial.print(Gamepad.Get_RAD_Joy_R());
  //   // Serial.print(" || ");
  //   // Serial.print(Gamepad.Get_POT_L());
  //   // Serial.print(" || ");
  //   // Serial.print(Gamepad.Get_POT_R());
  //   // Serial.print(" || ");
  //   // Serial.println(Gamepad.Get_status_button_90D_Right());
  // }

  Gamepad.getdata_Gamepad_I2C();

  DEG_joystick = constrain(Gamepad.Get_DEG_Joy_L(), 0, 360);
  if ((DEG_joystick >= 337.5) || (DEG_joystick < 22.5))
  {
    command = 'R';
    right();
  }
  else if (DEG_joystick >= 22.5 && DEG_joystick < 67.5)
  {
    command = 'I';
    forwardright();
  }
  else if (DEG_joystick >= 67.5 && DEG_joystick < 112.5)
  {
    command = 'F';
    forward();
  }
  else if (DEG_joystick >= 112.5 && DEG_joystick < 157.5)
  {
    command = 'G';
    forwardleft();
  }
  else if (DEG_joystick >= 157.5 && DEG_joystick < 202.5)
  {
    command = 'L';
    left();
  }
  else if (DEG_joystick >= 202.5 && DEG_joystick < 247.5)
  {
    command = 'H';
    backleft();
  }
  else if (DEG_joystick >= 247.5 && DEG_joystick < 292.5)
  {
    command = 'B';
    back();
  }
  else if (DEG_joystick >= 292.5 && DEG_joystick < 337.5)
  {
    command = 'J';
    backright();
  }

  if (Gamepad.Get_RAD_Joy_L() > 30)
  {
    Speed = map(Gamepad.Get_RAD_Joy_L(), 30, 512, 130, 255);
  }
  else
  {
    Speed = 0;
  }
  analogWrite(pwm_1, Speed);
  analogWrite(pwm_2, Speed);
}

void forward()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
}

void back()
{
  digitalWrite(in1, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);
}

void left()
{
  digitalWrite(in4, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
}

void right()
{
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in1, LOW);
  digitalWrite(in4, LOW);
}
void forwardleft()
{
  digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
}
void forwardright()
{
  digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
}
void backright()
{
  digitalWrite(in2, HIGH);
  digitalWrite(in4, LOW);
}
void backleft()
{
  digitalWrite(in2, LOW);
  digitalWrite(in4, HIGH);
}

void Stop()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
