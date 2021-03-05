// JeryDriver.h

#include "DefaultDriver.h"

#ifndef _JERYDRIVER_h
#define _JERYDRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class JerkyDriver : public DefaultDriver {
public:
	JerkyDriver(int pins[]) : DefaultDriver(pins) {};
	virtual void move(Direction dir, int speed = 200);
};

#endif

