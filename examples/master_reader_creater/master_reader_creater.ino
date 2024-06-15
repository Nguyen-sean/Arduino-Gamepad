// Wire Master Reader
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI slave device
// Refer to the "Wire Slave Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.

#include "MKE_Gamepad.h"
#include <Wire.h>


void setup() {
  Wire.begin();          // join I2C bus (address optional for master)
  Serial.begin(115200);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, sizeof(Data_MKE_Gamepad));  // request 6 bytes from slave device #8

  while (Wire.available()) {  // slave may send less than requested
    Wire.readBytes((char*)&Data_MKE_Gamepad, sizeof(Data_MKE_Gamepad));
    Serial.print(Data_MKE_Gamepad.DEG_Joy_L);
    Serial.print(" || ");
    Serial.print(Data_MKE_Gamepad.RAD_Joy_L);
    Serial.print(" ||<==>|| ");
    Serial.print(Data_MKE_Gamepad.DEG_Joy_R);
    Serial.print(" || ");
    Serial.print(Data_MKE_Gamepad.RAD_Joy_R);
    Serial.print(" || ");
    Serial.print(Data_MKE_Gamepad.pot_L);
    Serial.print(" || ");
    Serial.print(Data_MKE_Gamepad.pot_R);
    Serial.print(" || ");
    Serial.println(Data_MKE_Gamepad.buttons, BIN);
  }

  delay(10);
}
