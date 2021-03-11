/*
 Name:		KidCar.ino
 Created:	3/4/2021 12:39:38 PM
 Author:	kidro
*/

#include <IRremote.h>
#include "LoopHandler.h"
#include "DrivingBehavior.h"
#include "DrivingWithRemote.h"
#include "HBridgeDriver.h"

#define LED_PIN A0
#define TRIG_PIN 12
#define RECV_PIN 2

#define ENA 10
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENB 5

HBridgeDriver* driver;
DrivingBehavior* drivingBehavior;

void setup() {
	driver = new HBridgeDriver(ENA, IN1, IN2, IN3, IN4, ENB);
	drivingBehavior = new DrivingWithRemote(driver, RECV_PIN);
	drivingBehavior->init();

}

void loop() {
	drivingBehavior->onLoop();
}
