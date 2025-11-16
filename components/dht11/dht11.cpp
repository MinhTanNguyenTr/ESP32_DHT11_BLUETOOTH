/*
 * dht11.cpp
 *
 *  Created on: Nov 16, 2025
 *      Author: hi
 */


#include "dht11.h"
#include "driver/gpio.h"
#include "hal/gpio_types.h"
#include "soc/gpio_num.h"
#include "soc/gpio_sd_struct.h"
#include "esp_rom_sys.h"
DHT11::DHT11(gpio_num_t pin)
{
	gpio_set_direction(pin, GPIO_MODE_OUTPUT);
	gpio_set_pull_mode(pin, GPIO_FLOATING);
}

bool DHT11::waitforevent(int level, uint32_t timeout_us)
{
	uint32_t time = esp_timer_get_time();
	while(gpio_get_level(pin) != level)
	{
		if(esp_timer_get_time() - time > timeout_us) return false;
	}
	return true;
}

float DHT11::readTemperature() const {
	return temperature;
}

float DHT11::readHumility() const {
	return humility;
}

bool DHT11::read() {
	uint8_t data[5]= {0};
	
	gpio_set_direction(pin, GPIO_MODE_OUTPUT);
	gpio_set_level(pin, 0);
	esp_rom_delay_us(18000);
	gpio_set_level(pin, 1);
	esp_rom_delay_us(40);
	
	gpio_set_direction(pin, GPIO_MODE_INPUT);
	
	if(!waitforevent(0,80)) return false;
	if(!waitforevent(1, 80)) return false;
	
	for ( int i = 0 ; i < 40 ; i++)
	{
		if(!waitforevent(0, 50)) return false;
		uint32_t start = esp_timer_get_time();
		if(!waitforevent(1, 70)) return false;
		unit32_t len = esp_timer_get_time()	- start;
		data[i/8] <<=1;
		if(len > 40) data[i/8] |= 1;
		humility = data[0];
		temperature = data[2];
		return true;
	}
}