#ifndef MKE_Gamepad_SEAN__
#define MKE_Gamepad_SEAN__

#include "Arduino.h"

class MKE_Gamepad_joystick
{
private:
    uint8_t joystickXPin; // Chân analog cho trục X của joystick
    uint8_t joystickYPin; // Chân analog cho trục Y của joystick
    uint8_t buttonPin;    // Chân digital cho nút nhấn

    float x;
    float y;
    int xCenter = 512; // Giá trị trung tâm mặc định cho trục X
    int yCenter = 512; // Giá trị trung tâm mặc định cho trục Y
    int max_radius = 512;

    float radius;
    float angleDeg;
    void Joystick_configureCenter(); // Hàm cấu hình tọa độ trung tâm

public:
    void setup(uint8_t joystickXPin_, uint8_t joystickYPin_, uint8_t buttonPin_);

    float analogRead_Ox();

    float analogRead_Oy();

    float AngleDed();

    float Radius();
    float Radius_approximately(uint8_t num_approximately){
        return map(Radius(),0,max_radius,0,num_approximately);
    }
    
    void Serial_debug();
  

};

#endif