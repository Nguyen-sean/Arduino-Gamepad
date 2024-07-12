
/*
 * https://maniacbug.github.io/RF24/classRF24.html
 *
 * VCC - 3.3v
 * GND - GND
 * CSN - 10
 * CE - 9
 * SCK - 13 mặc định SPI
 * MOSI - 11 SPI
 * MISO - 12 SPI
 */
#include "MKL_Gamepad.h"

MKL_Gamepad Gamepad;
MKL_Gamepad_NRF24 MKL_NRF24;

RF24 radio(9, 10);              // CE, CSN
const byte diachi[6] = "12345"; // Mảng kí tự dạng chuỗi có 6 kí tự

void setup()
{
  Serial.begin(115200);
  Gamepad.Setup_Gamepad();

  while (!radio.begin())
  {
    Serial.println("Module không khởi động được...!!");
    delay(10);
  }

  radio.openWritingPipe(diachi);
  // openWritingPipe defaul là đường truyền 0
  // mở 1 kênh có địa chỉ 12345 trên đường truyền 0
  //  kênh này ghi data lên địa chỉ 12345
  radio.setPALevel(RF24_PA_MAX);
  // RF24_PA_<MIN
  // RF24_PA_LOW
  // RF24_PA_HIGH
  // RF24_PA_MAX
  // Power of NRF24 at MIN, MAX, HIGH, LOW
  radio.setChannel(80); // 125 kênh từ 0-124; TX và RX phải cùng kênh
                        // 2.4GHz ~ 2400Mhz, bước kênh là 1MHz
                        // setchannel(1) => 2401Mhz
                        // Cao nhất là 2525MHz, Tức là 2.525GHz

  radio.setDataRate(RF24_250KBPS); // Tốc độ truyền dữ liệu trong không khí
                                   // 250kbps, 1Mbps hoặc 2Mbps
                                   // 250 thấp nhất nhưng truyền xa, 1Mb và 2Mb mạnh nhưng truyền không xa
  /*
   * Tốc độ truyền dữ liệu không khí 2Mbps, băng thông 2MHz bị chiếm dụng nhiều tần số kênh
   * rộng hơn độ phân giải của cài đặt tần số kênh RF
   * Vì vậy, để đảm bảo các kênh không chồng chéo và giảm kết nối chéo ở chế độ 2Mbps
   * bạn cần giữ khoảng cách 2MHz giữa hai kênh.
   *
   * A: Xe TX-RX kênh 80, tốc độ truyền là 2Mb 80, 81, 82
   * B: Máy bay TX-RX kênh 83, tốc độ truyền là 250Kb
   */
  radio.stopListening(); // Cài đặt module là TX

  if (!radio.available())
  {
    Serial.println("Chưa kết nối được với RX...!!");
    Serial.println("CHỜ KẾT NỐI.......");
  }
}

void loop()
{

  Gamepad.getdata_Gamepad();
  radio.write(&Gamepad.Data_MKL_Gamepad, sizeof(Gamepad.Data_MKL_Gamepad));
  // &: Trả lại địa chỉ của một biến.
  // sizeof: trả về số byte bộ nhớ của một biến
  // hoặc là trả về tổng số byte bộ nhớ của một mảng

  // Serial.println(Data_MKL_Gamepad.buttons,BIN);
  // delay(1000);
}
