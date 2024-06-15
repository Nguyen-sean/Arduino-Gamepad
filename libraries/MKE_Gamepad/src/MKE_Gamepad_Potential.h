#ifndef MKE_Gamepad_Potential_SEAN__
#define MKE_Gamepad_Potential_SEAN__
#include "Arduino.h"
#include <MKE_SimpleKalmanFilter.h>

class MKE_Gamepad_Potential
{
private:
    MKE_SimpleKalmanFilter KalmanFilter;
    uint8_t _pin;

public:
    MKE_Gamepad_Potential() : KalmanFilter(2, 2, 0.01) {} // Khởi tạo KalmanFilter trong hàm tạo
    void setup(uint8_t pin);

    int readValue();
    int RawValue();
};

#endif
