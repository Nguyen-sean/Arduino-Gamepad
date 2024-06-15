#include "MKE_Gamepad.h"
#include <Wire.h>


void forward();
void back();
void left();
void right();
void forwardleft();
void forwardright();
void backright();
void backleft();
void Stop();


#define in1 9  //L298n Motor Driver pins.
#define in2 8
#define in3 7
#define in4 4

#define LED 13

#define pwm_1 6  // Speed motor
#define pwm_2 5

int command;
int Speed = 150;

char servo_compare = 'B';
char servo_compare_s = 'A';
void setup() {
  Wire.begin();  // join I2C bus (address optional for master)
  Serial.begin(115200);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(LED, OUTPUT);  //Set the LED pin.

  pinMode(pwm_1, OUTPUT);
  pinMode(pwm_2, OUTPUT);

  analogWrite(pwm_1, Speed);
  analogWrite(pwm_2, Speed);
}

void loop() {
  //  forward();
  //  delay(10000);
  Wire.requestFrom(8, sizeof(Data_MKE_Gamepad));
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
  Serial.println(Data_MKE_Gamepad.buttons, BIN);}


  



  // command = 'F';


  switch (command) {
    case 'F':
      forward();
      break;
    case 'B':
      back();
      break;
    case 'L':
      left();
      break;
    case 'R':
      right();
      break;
    case 'G':
      forwardleft();
      break;
    case 'I':
      forwardright();
      break;
    case 'H':
      backleft();
      break;
    case 'J':
      backright();
      break;
    case '0':
      Speed = 100;
      break;
    case '1':
      Speed = 105;
      break;
    case '2':
      Speed = 110;
      break;
    case '3':
      Speed = 130;
      break;
    case '4':
      Speed = 150;
      break;
    case '5':
      Speed = 170;
      break;
    case '6':
      Speed = 190;
      break;
    case '7':
      Speed = 210;
      break;
    case '8':
      Speed = 220;
      break;
    case '9':
      Speed = 230;

      break;
    case 'q':
      Speed = 255;
      break;
  }
  analogWrite(pwm_1, Speed);
  analogWrite(pwm_2, Speed);
}



void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in4, LOW);
}

void back() {
  digitalWrite(in2, HIGH);
  digitalWrite(in4, HIGH);
}

void left() {
  digitalWrite(in4, HIGH);
  digitalWrite(in1, HIGH);
}

void right() {
  digitalWrite(in3, HIGH);
  digitalWrite(in2, HIGH);
}
void forwardleft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in3, LOW);
}
void forwardright() {
  digitalWrite(in1, LOW);
  digitalWrite(in3, HIGH);
}
void backright() {
  digitalWrite(in2, HIGH);
  digitalWrite(in4, LOW);
}
void backleft() {
  digitalWrite(in2, LOW);
  digitalWrite(in4, HIGH);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
