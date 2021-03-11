/*
 Name:		KidCar.ino
 Created:	3/4/2021 12:39:38 PM
 Author:	kidro
*/

#include "LoopHandler.h"
#include "DrvingWithUltrasoundSensor.h"
#include "DrivingBehavior.h"
#include "HBridgeDriver.h"
#include "UltrasoundSensor.h"

#define LED_PIN A0
#define TRIG_PIN 12
#define ECHO_PIN 2

#define ENA 5
#define IN1 6
#define IN2 7
#define IN3 8
#define IN4 9
#define ENB 10

HBridgeDriver* driver;
UltrasoundSensor* sensor;
DrivingBehavior* drivingBehavior;

void setup() {
	driver = new HBridgeDriver(ENA, IN1, IN2, IN3, IN4, ENB);
	sensor = new UltrasoundSensor(TRIG_PIN, ECHO_PIN);
	drivingBehavior = new DrvingWithUltrasoundSensor(driver, sensor, LED_PIN);
	drivingBehavior->init();
}

void loop() {
	drivingBehavior->onLoop();
}
