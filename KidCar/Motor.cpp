#include "MotorDriver.h"
#include "Arduino.h"

Motor::Motor(int pins[])
{
	torquePin = pins[0];
	forwardPin = pins[1];
	reversePin = pins[2];

	pinMode(torquePin, OUTPUT);
	pinMode(forwardPin, OUTPUT);
	pinMode(reversePin, OUTPUT);
}

void Motor::setSpeed(int speed = 200)
{
	analogWrite(torquePin, speed);
}

void Motor::forward()
{
	digitalWrite(forwardPin, HIGH);
	digitalWrite(reversePin, LOW);
}

void Motor::reverse()
{
	digitalWrite(forwardPin, LOW);
	digitalWrite(reversePin, HIGH);
}
