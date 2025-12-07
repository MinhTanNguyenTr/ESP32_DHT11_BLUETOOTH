#ifndef COMPONENTS_DHT11_ISENSOR_INTERFACE_H_
#define COMPONENTS_DHT11_ISENSOR_INTERFACE_H_

class ISensor_Interface {
public:
    virtual ~ISensor_Interface() = default;

    virtual bool read() = 0;
    virtual float getTemperature() const = 0;
    virtual float getHumidity() const = 0;
};

#endif
