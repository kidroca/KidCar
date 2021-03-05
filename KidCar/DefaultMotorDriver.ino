#include "Motor.h"


class DefaultDriver : public MotorDriver {
public:
	DefaultDriver(int pins[]);
	virtual void move(Direction dir, int speed = 200);
private:
	Motor * leftSide;
	Motor * rightSide;
};


DefaultDriver::DefaultDriver(int pins[]) {
	leftSide = new Motor(pins);
	int righPins[] = { pins[3], pins[4], pins[5] };
	rightSide = new Motor(righPins);
}


void DefaultDriver::move(Direction dir, int speed)
{
	switch (dir)
	{
	case FORWARD:
		Serial.println("Moving forward");
		leftSide->setSpeed(speed);
		rightSide->setSpeed(speed);
		leftSide->forward();
		rightSide->forward();
		break;
	case REVERSE:
		leftSide->setSpeed(speed);
		rightSide->setSpeed(speed);
		leftSide->reverse();
		rightSide->reverse();
		break;
	case LEFT:
		leftSide->forward();
		rightSide->forward();
		rightSide->setSpeed(0);
		break;
	case RIGHT:
		leftSide->forward();
		rightSide->forward();
		leftSide->setSpeed(0);
		break;
	default:
		break;
	}
}

