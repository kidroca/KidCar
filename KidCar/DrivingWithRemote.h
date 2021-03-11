#pragma once

#include "DrivingBehavior.h"
#include "IRremoteInt.h"

class DrivingWithRemote : public DrivingBehavior
{
public:
	DrivingWithRemote(HBridgeDriver * driver, int recvpin)
		: DrivingBehavior(driver), reciever(recvpin)
	{}
	void init();
	void onLoop();
private:
	IRrecv reciever;
	unsigned long lastRecievedAtMs{ 0 };
	uint32_t lastCommand{ 0 };
	bool autoForward{ false };
};

