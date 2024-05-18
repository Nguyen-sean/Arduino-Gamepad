#include <math.h>

const int joystickXPin = A0; // Chân analog cho trục X của joystick
const int joystickYPin = A1; // Chân analog cho trục Y của joystick
const int buttonPin = 2; // Chân digital cho nút nhấn

int xCenter = 512; // Giá trị trung tâm mặc định cho trục X
int yCenter = 512; // Giá trị trung tâm mặc định cho trục Y

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); // Kích hoạt điện trở kéo lên cho nút nhấn

  Serial.println("Nhấn nút để cấu hình tọa độ trung tâm...");

  // Chờ nhấn nút để bắt đầu cấu hình
  while (digitalRead(buttonPin) == HIGH) {
    delay(10);
  }
  delay(500); // Chờ để tránh nhầm lẫn từ lần nhấn nút

  configureCenter();
  Serial.println("Cấu hình hoàn tất.");
}

void loop() {
  // Đọc giá trị từ joystick và lọc nhiễu bằng cách lấy trung bình từ nhiều lần đọc
  int xValue = readAnalogFiltered(joystickXPin);
  int yValue = readAnalogFiltered(joystickYPin);

  // Chuyển đổi giá trị theo tọa độ trung tâm
  float x = xValue - xCenter;
  float y = yValue - yCenter;

  // Tính bán kính (khoảng cách từ gốc tọa độ)
  float radius = sqrt(x * x + y * y);

  // Tính góc theo radians và chuyển đổi sang độ
  float angleRad = atan2(y, x);
  float angleDeg = angleRad * (180.0 / PI);

  // Điều chỉnh góc để nằm trong khoảng từ 0 đến 360 độ
  if (angleDeg < 0) {
    angleDeg += 360.0;
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

  delay(200); // Đợi 200ms trước khi đọc lại
}

// Hàm cấu hình tọa độ trung tâm
void configureCenter() {
  long xSum = 0;
  long ySum = 0;
  const int sampleCount = 100; // Số lần đọc để lấy trung bình

  for (int i = 0; i < sampleCount; i++) {
    xSum += analogRead(joystickXPin);
    ySum += analogRead(joystickYPin);
    delay(10); // Đợi 10ms giữa các lần đọc
  }

  xCenter = xSum / sampleCount;
  yCenter = ySum / sampleCount;

  Serial.print("Tọa độ trung tâm X: ");
  Serial.println(xCenter);
  Serial.print("Tọa độ trung tâm Y: ");
  Serial.println(yCenter);
}

// Hàm đọc giá trị analog và lọc nhiễu
int readAnalogFiltered(int pin) {
  long sum = 0;
  const int sampleCount = 10; // Số lần đọc để lấy trung bình

  for (int i = 0; i < sampleCount; i++) {
    sum += analogRead(pin);
    delay(5); // Đợi 5ms giữa các lần đọc
  }

  return sum / sampleCount;
}
