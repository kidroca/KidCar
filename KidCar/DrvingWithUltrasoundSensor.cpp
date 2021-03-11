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

void DrvingWithUltrasoundSensor::onLoop()
{
	sensor->onLoop();

	unsigned int distance = sensor->getRange();

	if (distance < THRESHOLD) {
		//evade();
	}
	else if (isStuck(distance)) {
		digitalWrite(ledPin, HIGH);
		//evade();
		digitalWrite(ledPin, LOW);
	}
	else {
		unsigned int nextSpeed = map(distance, THRESHOLD, FAR, CASUAL, FURY);
		apply(FORWARD, constrain(nextSpeed, CASUAL, FURY));
	}
}

void DrvingWithUltrasoundSensor::evade()
{
	apply(FORWARD, STOP);
	delay(150);
	apply(REVERSE, HASTE);
	delay(250);

	apply(REVERSE, STOP);
	delay(300);

	const uint16_t scanSize = 6;
	unsigned int maxDistance = 0;
	uint16_t farthest = scanSize / 2;

	Direction scanDirection = random(0, 1) ? RIGHT : LEFT;

	for (uint16_t i = 1; i <= scanSize; i++)
	{
		apply(scanDirection, FURY);
		delay(200);
		apply(scanDirection, STOP);
		delay(125);

		unsigned int nextDistance = sensor->measure();

		if (nextDistance > maxDistance) {
			farthest = i;
			maxDistance = nextDistance;
		}
	}

	Direction backTrackDirection = scanDirection == RIGHT ? LEFT : RIGHT;

	for (uint16_t i = scanSize; i > farthest; i--)
	{
		apply(backTrackDirection, FURY);
		delay(200);
		apply(backTrackDirection, STOP);
		delay(125);
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
