#include "DHT11.h"
#include "esp_rom_sys.h"
#include "esp_log.h"

static const char* TAG = "DHT11";

DHT11::DHT11(gpio_num_t pin)
    : m_pin(pin), m_temperature(0), m_humidity(0) 
{
    gpio_set_direction(m_pin, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(m_pin, GPIO_PULLUP_ONLY);
    gpio_set_level(m_pin, 1);
}

bool DHT11::read() 
{
    uint8_t data[5] = {0};

    if (!readRaw(data)) {
        ESP_LOGE(TAG, "Failed to read sensor data");
        return false;
    }

    uint8_t checksum = data[0] + data[1] + data[2] + data[3];
    if (checksum != data[4]) {
        ESP_LOGE(TAG, "Checksum mismatch: expected %d, got %d", checksum, data[4]);
        return false;
    }

    m_humidity = data[0];
    m_temperature = data[2];
    return true;
}

bool DHT11::readRaw(uint8_t data[5]) 
{

    gpio_set_direction(m_pin, GPIO_MODE_OUTPUT);
    gpio_set_level(m_pin, 0);
    esp_rom_delay_us(20000);

    gpio_set_level(m_pin, 1);
    esp_rom_delay_us(40);
    gpio_set_direction(m_pin, GPIO_MODE_INPUT);

    int timeout = 0;

    // Wait LOW 80us
    while (gpio_get_level(m_pin) == 1 && timeout++ < 100)
        esp_rom_delay_us(1);
    if (timeout >= 100) return false;

    timeout = 0;
    while (gpio_get_level(m_pin) == 0 && timeout++ < 100)
        esp_rom_delay_us(1);
    if (timeout >= 100) return false;

    timeout = 0;
    while (gpio_get_level(m_pin) == 1 && timeout++ < 100)
        esp_rom_delay_us(1);
    if (timeout >= 60) return false;

    for (int i = 0; i < 40; i++) 
    {

        timeout = 0;
        while (gpio_get_level(m_pin) == 0 && timeout++ < 100)
            esp_rom_delay_us(1);
        if (timeout >= 100) return false;

        // đo độ rộng xung HIGH
        int t = 0;
        while (gpio_get_level(m_pin) == 1) {
            t++;
            esp_rom_delay_us(1);
            if (t > 120) break;
        }

        data[i / 8] <<= 1;
        if (t > 40)
            data[i / 8] |= 1;
    }

    return true;
}
