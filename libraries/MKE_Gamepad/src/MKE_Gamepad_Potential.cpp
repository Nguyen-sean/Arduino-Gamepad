#include "MKE_Gamepad_Potential.h"

void MKE_Gamepad_Potential::setup(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, INPUT);
}

int MKE_Gamepad_Potential::readValue()
{
    return KalmanFilter.updateEstimate(map(analogRead(_pin), 0, 1024, 1024, 0));
}
int MKE_Gamepad_Potential::RawValue()
{
    return map(analogRead(_pin), 0, 1024, 1024, 0);
}