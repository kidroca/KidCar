/*
 Name:		KidCar.ino
 Created:	3/4/2021 12:39:38 PM
 Author:	kidro
*/

#include "JerkyDriver.h"
#include "UltrasoundSensor.h"
#include "MotorDriver.h"
#include "DefaultDriver.h"

#define LED_PIN A0
#define TRIG_PIN 12
#define ECHO_PIN 2
#define ECHO_INT 0
#define STUCK_CHECK_INTERVAL 2200

enum SPEED {
	FURY = 255,
	HASTE = 210,
	CASUAL = 165,
	CAUTIOUS = 120,
	CRAWL = 80,
	STOP = 0,
};

enum DISTANCE {
	VERY_FAR = 400,
	FAR = 260,
	MEDIUM = 160,
	EVADE = 60,
	NEAR = 80,
	THRESHOLD = 33,
};

unsigned int distance = THRESHOLD;
unsigned int pastDistance = FAR;

Direction direction = REVERSE;
SPEED speed = CASUAL;

int MOTOR_PINS[] = {
	10, // eng left analog
	9, // eng left in1 fwd
	8, // eng left in2 rwd
	5, // eng right analog
	6, // eng right in4 fwd
	7, // eng right in3 rwd
};

MotorDriver* driver;
UltrasoundSensor sensor(TRIG_PIN, ECHO_PIN, ECHO_INT);

unsigned int saveDistance(unsigned int nextDistance) {
	if (nextDistance > VERY_FAR) nextDistance = VERY_FAR;

	distance = nextDistance;
	return distance;
}

void drive(Direction nextDir, SPEED nextSpeed) {
	if (direction != nextDir || speed != nextSpeed) {
		driver->move(nextDir, nextSpeed);

		speed = nextSpeed;
		direction = nextDir;
	}
}

void evade() {
	drive(FORWARD, STOP);
	delay(150);
	drive(REVERSE, HASTE);
	delay(250);

	drive(RIGHT, CASUAL);
	sensor.start();
	while (distance < EVADE) {
		if (sensor.isFinished()) {
			unsigned int measured = sensor.getRange();
			distance = saveDistance(measured);
			delay(50);
			sensor.start();
		}
	}

	drive(RIGHT, CASUAL);
	delay(250);
	drive(RIGHT, STOP);
	delay(250);
}

bool isStuck() {
	static unsigned long pastDistanceLastCheckMs = 0;
	if (millis() - pastDistanceLastCheckMs >= STUCK_CHECK_INTERVAL) {
		bool stuck = abs(distance - pastDistance) <= 3;
		pastDistance = distance;
		pastDistanceLastCheckMs = millis();

		return stuck;
	}

	return false;
}

void setup() {
	pinMode(LED_PIN, OUTPUT);
	driver = new JerkyDriver(MOTOR_PINS);

	sensor.init();
	sensor.start();
}

void loop() {
	if (sensor.isFinished()) {
		unsigned int measured = sensor.getRange();
		distance = saveDistance(measured);

		if (distance < THRESHOLD) {
			evade();
		}
		else if (isStuck()) {
			digitalWrite(LED_PIN, HIGH);
			evade();
			digitalWrite(LED_PIN, LOW);
		}
		else if (distance < NEAR) {
			drive(FORWARD, CRAWL);
		}
		else if (distance < MEDIUM) {
			drive(FORWARD, CAUTIOUS);
		}
		else if (distance < FAR) {
			drive(FORWARD, CASUAL);
		}
		else if (distance < VERY_FAR) {
			drive(FORWARD, HASTE);
		}
		else {
			drive(FORWARD, FURY);
		}

		delay(50);
		sensor.start();
	}
}
