#include "MotorDriver.h"
#include "DefaultDriver.h"

DefaultDriver::DefaultDriver(int pins[]) {
	leftSide = new Motor(pins);
	int righPins[] = { pins[3], pins[4], pins[5] };
	rightSide = new Motor(righPins);
}

void DefaultDriver::move(Direction dir, int speed = 200)
{
	leftSide->setSpeed(speed);
	rightSide->setSpeed(speed);

	switch (dir)
	{
	case FORWARD:
		leftSide->forward();
		rightSide->forward();
		break;
	case REVERSE:
		leftSide->reverse();
		rightSide->reverse();
		break;
	case LEFT:
		leftSide->setSpeed(0);
		break;
	case RIGHT:
		rightSide->setSpeed(0);
		break;
	default:
		break;
	}
}


