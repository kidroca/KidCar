// DrivingBehavior.h

#ifndef _DRIVINGBEHAVIOR_h
#define _DRIVINGBEHAVIOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	#include "HBridgeDriver.h"
	#include "LoopHandler.h"
#else
	#include "WProgram.h"
#endif

class DrivingBehavior: LoopHandler
{
protected:
	HBridgeDriver * motorDriver;
	Direction direction;
	int speed;

	void apply(Direction nextDir, int nextSpeed)
	{
		if (direction != nextDir || speed != nextSpeed) {
			motorDriver->move(nextDir, nextSpeed);

			speed = nextSpeed;
			direction = nextDir;
		}
	}

 public:
	 DrivingBehavior(HBridgeDriver * driver)
	 {
		 motorDriver = driver;
	 };
	 virtual void onLoop() = 0;
	 virtual void init() { motorDriver->init(); };
	 virtual void stop() { motorDriver->move(FORWARD, 0); direction = NONE; };
};

#endif

