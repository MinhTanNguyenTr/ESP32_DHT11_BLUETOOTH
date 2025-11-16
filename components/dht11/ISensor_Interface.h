/*
 * ISensor_Interface.h
 *
 *  Created on: Nov 16, 2025
 *      Author: hi
 */

#ifndef COMPONENTS_DHT11_ISENSOR_INTERFACE_H_
#define COMPONENTS_DHT11_ISENSOR_INTERFACE_H_

class ISensor_Interface {
	private:
	public:
	virtual ~ISensor_Interface();
	virtual bool read() = 0;
	virtual float readTemperature() const = 0;
	virtual float readHumility() const =0;
};



#endif /* COMPONENTS_DHT11_ISENSOR_INTERFACE_H_ */
