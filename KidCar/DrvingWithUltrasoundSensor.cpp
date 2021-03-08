#include "DrvingWithUltrasoundSensor.h"

enum DISTANCE {
	VERY_FAR = 400,
	FAR = 260,
	MEDIUM = 160,
	EVADE = 60,
	NEAR = 80,
	THRESHOLD = 33,
};

enum Speed {
	FURY = 255,
	HASTE = 210,
	CASUAL = 165,
	CAUTIOUS = 120,
	CRAWL = 80,
	STOP = 0,
};

void DrvingWithUltrasoundSensor::init()
{
	DrivingBehavior::init();
	sensor->init();
	pinMode(ledPin, OUTPUT);
}

void DrvingWithUltrasoundSensor::drive()
{
	unsigned int distance = sensor->measure();

	if (distance < THRESHOLD) {
		evade();
	}
	else if (isStuck(distance)) {
		digitalWrite(ledPin, HIGH);
		evade();
		digitalWrite(ledPin, LOW);
	}
	else if (distance < NEAR) {
		apply(FORWARD, CRAWL);
	}
	else if (distance < MEDIUM) {
		apply(FORWARD, CAUTIOUS);
	}
	else if (distance < FAR) {
		apply(FORWARD, CASUAL);
	}
	else if (distance < VERY_FAR) {
		apply(FORWARD, HASTE);
	}
	else {
		apply(FORWARD, FURY);
	}

	delay(50);
}


void DrvingWithUltrasoundSensor::apply(Direction nextDir, int nextSpeed)
{
	if (direction != nextDir || speed != nextSpeed) {
		motorDriver->move(nextDir, nextSpeed);

		speed = nextSpeed;
		direction = nextDir;
	}
}

void DrvingWithUltrasoundSensor::evade()
{
	apply(FORWARD, STOP);
	delay(150);
	apply(REVERSE, HASTE);
	delay(300);

	while (sensor->measure() < EVADE) {
		apply(RIGHT, CASUAL);
		delay(200);
		apply(RIGHT, STOP);
		delay(200);
	}
}

bool DrvingWithUltrasoundSensor::isStuck(const unsigned int distance)
{
	if (millis() - pastDistanceLastCheckMs >= STUCK_CHECK_INTERVAL) {
		bool stuck = abs(distance - pastDistance) <= 3;
		pastDistance = distance;
		pastDistanceLastCheckMs = millis();

		return stuck;
	}

	return false;
}
