// HC_SR04.h

#ifndef _Ultrasound_Sensor_h
#define _Ultrasound_Sensor_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class UltrasoundSensor {
public:
    UltrasoundSensor(int trigger, int echo, int interrupt, int max_dist = 400);

    void init();
    void start();
    unsigned int measure();
    bool isFinished();
    unsigned int getRange();
    static UltrasoundSensor* instance() { return _instance; }

private:
    static void _echo_isr();

    int _trigger, _echo, _int, _max;
    volatile unsigned long _start, _end;
    volatile bool _finished;
    static UltrasoundSensor* _instance;
};

#endif

