#ifndef MKL_Gamepad_Potential_SEAN__
#define MKL_Gamepad_Potential_SEAN__
#include "Arduino.h"
#include <MKL_SimpleKalmanFilter.h>

class MKL_Gamepad_Potential
{
private:
    MKL_SimpleKalmanFilter KalmanFilter;
    uint8_t _pin;

public:
    MKL_Gamepad_Potential() : KalmanFilter(1, 2, 0.01) {} // Khởi tạo KalmanFilter trong hàm tạo
    void setup(uint8_t pin);

    int readValue();
    int RawValue();
};

#endif
