#ifndef _HBridgeDriver_h
#define _HBridgeDriver_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

enum Direction {
	FORWARD,
	REVERSE,
	LEFT,
	RIGHT,
	NONE,
};

class HBridgeDriver {
private:
	int enA, in1, in2, in3, in4, enB;
	static HBridgeDriver* _instance;

public:
	HBridgeDriver(int enA, int in1, int in2, int in3, int in4, int enB);
	void init();
	void move(Direction dir, int speed = 200);
};

#endif