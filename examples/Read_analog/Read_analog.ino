#include <Arduino.h>

#include <MKE_SimpleKalmanFilter.h>
MKE_SimpleKalmanFilter SimpleKalmanFilter_Ox(2, 2, 0.01);
MKE_SimpleKalmanFilter SimpleKalmanFilter_Oy(2, 2, 0.01);

const int joystickXPin = A0;
const int joystickYPin = A1;
const int buttonPin = 2;

int xCenter = 512;
int yCenter = 512;

int Oy_read()
{
  return SimpleKalmanFilter_Oy.updateEstimate(analogRead(joystickYPin));
}

int Ox_read()
{
  return SimpleKalmanFilter_Ox.updateEstimate(analogRead(joystickXPin));
}

void configureCenter()
{
  long xSum = 0;
  long ySum = 0;
  const int sampleCount = 100; // Số lần đọc để lấy trung bình

  for (int i = 0; i < sampleCount; i++)
  {
    xSum += analogRead(joystickXPin);
    ySum += analogRead(joystickYPin);
    delay(10);
  }

  xCenter = xSum / sampleCount;
  yCenter = ySum / sampleCount;

  Serial.print("Tọa độ trung tâm X: ");
  Serial.println(xCenter);
  Serial.print("Tọa độ trung tâm Y: ");
  Serial.println(yCenter);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(joystickXPin, INPUT);
  pinMode(joystickYPin, INPUT);
  configureCenter();
  delay(1000);
}

void loop()
{

  // Serial.println(SimpleKalmanFilter_Ox.updateEstimate(analogRead(joystickXPin)),0);
  Serial.print(Ox_read());
  Serial.print(" || ");
  Serial.println(Oy_read());
}
