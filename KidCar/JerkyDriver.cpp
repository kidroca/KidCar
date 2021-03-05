#include "JerkyDriver.h"

void JerkyDriver::move(Direction dir, int speed)
{
	DefaultDriver::move(dir, speed);

	leftSide->setSpeed(speed);
	rightSide->setSpeed(speed);

	switch (dir)
	{
	case LEFT:
		rightSide->forward();
		leftSide->reverse();
		break;
	case RIGHT:
		leftSide->forward();
		rightSide->reverse();
		break;
	default:
		break;
	}
}
