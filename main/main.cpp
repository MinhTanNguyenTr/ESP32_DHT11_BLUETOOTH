#include "SensorManager.h"
#include "dht11.h"
#include "BluetoothManager.h"

extern "C" void app_main() 
{

    // Bluetooth
    BluetoothManager bt("ESP32_DHT11");
    bt.init();

    bt.onData([](const char* msg) {
        printf("Received from phone: %s\n", msg);
    });

    // Sensor
    SensorManager sm;
    auto* dht = new DHT11(GPIO_NUM_2);
    sm.addSensor(dht);

    while (true) {
        if (dht->read()) {
            float t = dht->getTemperature();
            float h = dht->getHumidity();

            char buffer[64];
            sprintf(buffer, "Temp=%.1fC Hum=%.1f%%\n", t, h);

            bt.sendMessage(buffer);
            ESP_LOGI("MAIN", "%s", buffer);
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
