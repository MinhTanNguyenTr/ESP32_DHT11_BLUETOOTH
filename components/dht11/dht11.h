#ifndef COMPONENTS_DHT11_DHT11_HPP_
#define COMPONENTS_DHT11_DHT11_HPP_

#include "driver/gpio.h"
#include "ISensor_Interface.h"

class DHT11 : public ISensor_Interface {
public:
    explicit DHT11(gpio_num_t pin);

    bool read() override;
    float getTemperature() const override { return m_temperature; }
    float getHumidity() const override { return m_humidity; }

private:
    bool readRaw(uint8_t data[5]);

private:
    gpio_num_t m_pin;
    float m_temperature;
    float m_humidity;
};

#endif
