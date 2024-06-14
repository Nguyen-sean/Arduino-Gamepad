#include<Arduino.h>

void setup() {
  // Khởi động Serial Monitor ở baud rate 9600
  Serial.begin(115200);
  
  // Cấu hình tất cả các chân digital là đầu vào
  for (int i = 2; i <= 13; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);
}

void loop() {
  // Đọc các chân digital
  Serial.println("Digital Pins:");
  for (int i = 2; i <= 13; i++) {
    int state = digitalRead(i);
    Serial.print("Pin ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(state);
  }

  // Đọc các chân analog
  Serial.println("Analog Pins:");
  for (int i = 0; i <= 7; i++) {
    int value = analogRead(i);
    Serial.print("Pin A");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(value);
  }

  // Chờ 1 giây trước khi đọc lại
  delay(200);
}
