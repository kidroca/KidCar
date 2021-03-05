#pragma once

#include "MotorDriver.h"

class DefaultDriver : public MotorDriver {
public:
	DefaultDriver(int pins[]);
	virtual void move(Direction dir, int speed = 200);
protected:
	Motor* leftSide;
	Motor* rightSide;
};

