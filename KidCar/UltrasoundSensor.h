// HC_SR04.h

#ifndef _Ultrasound_Sensor_h
#define _Ultrasound_Sensor_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
    #include "LoopHandler.h"
#else
	#include "WProgram.h"
#endif

class UltrasoundSensor: LoopHandler {
public:
    UltrasoundSensor(int trigger, int echo, int max_dist = 500);

    void init();
    void onLoop();
    unsigned int measure();
    unsigned int getRange();
    static UltrasoundSensor* instance() { return _instance; }

private:
    int _trigger, _echo, _max, _phase;
    unsigned long _phaseTime { 0 };
    unsigned long _pulseTime { 0 };
    static UltrasoundSensor* _instance;
};

#endif

