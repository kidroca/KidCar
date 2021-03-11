// DrvingWithUltrasoundSensor.h

#ifndef _DRVINGWITHULTRASOUNDSENSOR_h
#define _DRVINGWITHULTRASOUNDSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "DrivingBehavior.h"
	#include "UltrasoundSensor.h"

	#define STUCK_CHECK_INTERVAL 2200
#else
	#include "WProgram.h"
#endif

class DrvingWithUltrasoundSensor : public DrivingBehavior
{
 public:
	 DrvingWithUltrasoundSensor(HBridgeDriver * driver, UltrasoundSensor * sensor, int ledPin) 
		 : DrivingBehavior(driver), sensor(sensor), ledPin(ledPin)
	  {}
	 void init();
	 void onLoop();

private:
	UltrasoundSensor* sensor;
	Direction direction;
	int speed;
	int ledPin;
	unsigned long pastDistanceLastCheckMs { 0 };
	unsigned long pastDistance { 0 };

	void apply(Direction nextDir, int nextSpeed);
	void evade();
	bool isStuck(unsigned int distance);
};

#endif

