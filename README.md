<img width="902" height="500" alt="image" src="https://github.com/user-attachments/assets/32e880be-8890-4234-a57b-3d30a5b94a34" />ESP-IDF template app
====================
ESP set chân đọc data từ 1 xuống 0 và duy trì nó trong ít nhất 18 mili giây, sau đó kéo lên 1 và duy trì trong 20->40 micro giây, để thông báo cho DHT11 biết rằng "tui đang muốn đọc data"
[EN] ESP sets the pin to read data from 1 to 0 and holds it for at least 18 milliseconds, then pulls it up to 1 and holds it for 20->40 microseconds, to let the DHT11 know that "I want to read data".
Sau đó, DHT11 phản hồi bằng cách kéo chân data xuống 0 trong ít nhất 80 giây và kéo chân data lên 1 trong ít nhất 80 giây nhằm thông báo cho MCU " tôi sẵn sàng gửi data".
[EN] Then, the DHT11 responds by pulling the data pin low for at least 80 microseconds and pulling the data pin high for at least 80 microseconds to notify the MCU, "I'm ready to send data."
<img width="903" height="476" alt="image" src="https://github.com/user-attachments/assets/a9a68fda-ce78-435f-ba10-39581ee923fc" />
<img width="880" height="429" alt="image" src="https://github.com/user-attachments/assets/0f6dbb45-8e20-4e47-9105-5d0cbd44020c" />

Khi DHT11 gửi dữ liệu, dữ liệu sẽ bao gồm 5 byte (40 bits), cách mà DHT11 mã hóa bit đó là: DHT11 kéo chân data xuống 0 trong 50 micro giây, sau đó thì kéo lên 1, trong đó nếu kéo lên mức 1 trong khoảng 26->28 micro giây, đó là bit 0, nếu kéo lên mức 1 trong khoảng 70 micro giây thì đó là bit 1. 
[EN] When the DHT11 sends data, the data will consist of 5 bytes (40 bits). The way DHT11 encodes a bit is: it pulls the data line down to 0 for 50 microseconds, then pulls it up to 1. If it pulls up to 1 for about 26-28 microseconds, that represents a bit 0; if it pulls up to 1 for about 70 microseconds, that represents a bit 1.
This is a template application to be used with [Espressif IoT Development Framework](https://github.com/espressif/esp-idf).

Please check [ESP-IDF docs](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) for getting started instructions.
Please check [DHT11 datasheet] (https://www.alldatasheet.com/datasheet-pdf/pdf/1132088/ETC2/DHT11.html)

