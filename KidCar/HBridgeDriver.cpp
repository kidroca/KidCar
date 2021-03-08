#include "HBridgeDriver.h"
#include "Arduino.h"

HBridgeDriver::HBridgeDriver(int enA, int in1, int in2, int in3, int in4, int enB)
	: enA(enA), in1(in1), in2(in2), in3(in3), in4(in4), enB(enB)
{
}

void HBridgeDriver::init()
{
	pinMode(enA, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	pinMode(enB, OUTPUT);
}

void HBridgeDriver::move(Direction dir, int speed = 200)
{
	analogWrite(enA, speed);
	analogWrite(enB, speed);

	switch (dir)
	{
	case FORWARD:
		digitalWrite(in1, HIGH);
		digitalWrite(in2, LOW);
		digitalWrite(in4, HIGH);
		digitalWrite(in3, LOW);
		break;
	case REVERSE:
		digitalWrite(in1, LOW);
		digitalWrite(in2, HIGH);
		digitalWrite(in4, LOW);
		digitalWrite(in3, HIGH);
		break;
	case LEFT:
		digitalWrite(in1, LOW);
		digitalWrite(in2, HIGH);
		digitalWrite(in4, HIGH);
		digitalWrite(in3, LOW);
		break;
	case RIGHT:
		digitalWrite(in1, HIGH);
		digitalWrite(in2, LOW);
		digitalWrite(in4, LOW);
		digitalWrite(in3, HIGH);
		break;
	default:
		break;
	}
}
