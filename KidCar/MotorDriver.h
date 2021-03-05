#pragma once

#include "Arduino.h"

struct Motor
{
public:
	Motor(int pins[]);
	void setSpeed(int speed = 200);
	void forward();
	void reverse();
private:
	int torquePin;
	int forwardPin;
	int reversePin;
};

enum Direction {
	FORWARD,
	REVERSE,
	LEFT,
	RIGHT
};

class MotorDriver {
public:
	virtual void move(Direction dir, int speed = 200) = 0;
};

