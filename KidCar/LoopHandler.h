// LoopHandler.h

#ifndef _LOOPHANDLER_h
#define _LOOPHANDLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class LoopHandler
{
 protected:


 public:
	virtual void onLoop() = 0;
};

#endif

