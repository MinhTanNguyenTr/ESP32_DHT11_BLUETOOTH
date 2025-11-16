/*
 * dht11.h
 *
 *  Created on: Nov 16, 2025
 *      Author: hi
 */

#ifndef COMPONENTS_DHT11_DHT11_H_
#define COMPONENTS_DHT11_DHT11_H_

#include "ISensor_Interface.h"
#include "driver/gpio.h"
#include "soc/gpio_num.h"
class DHT11 {
	private:
	gpio_num_t gpio_pinl
	float temperature;
	float humility;
	bool waitforevent(int level, uint32_t timeout_us);
	public:
	explicit DHT11(gpio_num_t _pin);
	bool read() override;
	float readTemperature() const override;
	float readHumility() const override;
};




#endif /* COMPONENTS_DHT11_DHT11_H_ */
