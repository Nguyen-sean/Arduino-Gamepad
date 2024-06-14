#include <Arduino.h>
#include <math.h>

#define joystickXPin A0 // Chân analog cho trục X của joystick
#define joystickYPin A1 // Chân analog cho trục Y của joystick
#define buttonPin 2     // Chân digital cho nút nhấn

float x;
float y;
int xCenter = 512; // Giá trị trung tâm mặc định cho trục X
int yCenter = 512; // Giá trị trung tâm mặc định cho trục Y
int max_radius = 512;

float radius;
float angleDeg;

void setup()
{
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP); // Kích hoạt điện trở kéo lên cho nút nhấn
  pinMode(8, OUTPUT);
  Serial.println("Nhấn nút để cấu hình tọa độ trung tâm...");

  // Chờ nhấn nút để bắt đầu cấu hình
  while (digitalRead(buttonPin) == HIGH)
  {
  }
  delay(500); // Chờ để tránh nhầm lẫn từ lần nhấn nút

  configureCenter();
  Serial.println("Cấu hình hoàn tất.");
}

void loop()
{
  // Chuyển đổi giá trị theo tọa độ trung tâm
  x = map(analogRead(joystickXPin), 0, 1024, 1024, 0) - xCenter;
  y = analogRead(joystickYPin) - yCenter;

  if (((-5 < x) && (x < 5)) && ((-5 < y) && (y < 5)))
  {
    angleDeg = 0;
    radius = 0;
  }
  else
  {
    // Tính bán kính (khoảng cách từ gốc tọa độ)
    radius = sqrt(x * x + y * y);
    if (radius > max_radius)
    {
      radius = max_radius;
    }

    angleDeg = atan2(y, x) * (180.0 / PI);

    // Điều chỉnh góc để nằm trong khoảng từ 0 đến 360 độ
    if (angleDeg < 0)
    {
      angleDeg += 360.0;
    }
  }

  // In kết quả
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Góc: ");
  Serial.print(angleDeg);
  Serial.print(" độ");
  Serial.print(" Bán kính: ");
  Serial.println(radius);

  // Đợi 200ms trước khi đọc lại
}

// Hàm cấu hình tọa độ trung tâm
void configureCenter()
{
  long xSum = 0;
  long ySum = 0;
  const int sampleCount = 200; // Số lần đọc để lấy trung bình

  for (int i = 0; i < sampleCount; i++)
  {
    xSum += map(analogRead(joystickXPin), 0, 1024, 1024, 0);
    ySum += analogRead(joystickYPin);
    delay(10); // Đợi 10ms giữa các lần đọc
  }

  xCenter = xSum / sampleCount;
  yCenter = ySum / sampleCount;

  max_radius = min(min(xCenter,1024-xCenter),min(yCenter,1024-yCenter));
  digitalWrite(8, HIGH);
  delay(300);
  digitalWrite(8, LOW);

  Serial.print("Tọa độ trung tâm X: ");
  Serial.println(xCenter);
  Serial.print("Tọa độ trung tâm Y: ");
  Serial.println(yCenter);
}
