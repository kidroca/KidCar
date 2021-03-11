#include "DrivingWithRemote.h"

void DrivingWithRemote::init()
{
	DrivingBehavior::init();
	speed = 150;
	reciever.start();
}

void DrivingWithRemote::onLoop()
{
	if (reciever.decode())
	{
		lastRecievedAtMs = millis();

		switch (reciever.decodedIRData.decodedRawData)
		{
		case 3018249515: motorDriver->move(FORWARD, speed); break;
		case 107678027: {
			motorDriver->move(REVERSE, speed);
			autoForward = false;
			break;
		}
		case 1654297351: motorDriver->move(LEFT, speed); break;
		case 317438763: motorDriver->move(RIGHT, speed); break;
		case 2188863791: {
			if (speed == 0) speed = 150;
			if (speed < 260) speed += 10;
			break;
		}
		case 3406441423: if (speed > 100) speed -= 10; break;
		case 2578179759: autoForward = true; break;
		case 807711435: autoForward = false; break;
		default:
			break;
		}

		reciever.resume();
	}
	
	if (millis() - lastRecievedAtMs > 180) {
		if (autoForward) {
			motorDriver->move(FORWARD, speed);
		}
		else {
			stop();
		}
	}
}
