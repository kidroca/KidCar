#include "UltrasoundSensor.h"
#include "Arduino.h"

UltrasoundSensor* UltrasoundSensor::_instance(NULL);

UltrasoundSensor::UltrasoundSensor(int trigger, int echo, int max_dist)
    : _trigger(trigger), _echo(echo), _max(max_dist * 58), _finished(false)
{
    if (_instance == 0) _instance = this;
}

void UltrasoundSensor::init() {
    pinMode(_trigger, OUTPUT);
    pinMode(_echo, INPUT);

    //attachInterrupt(digitalPinToInterrupt(_echo), _echo_isr, CHANGE);
}

void UltrasoundSensor::start() {
    _finished = false;
    digitalWrite(_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigger, LOW);
}

unsigned int UltrasoundSensor::measure()
{
    start();
    return pulseIn(_echo, HIGH, _max) / 58;
}

unsigned int UltrasoundSensor::getRange() {
    return (_end - _start) / 58;
}

bool UltrasoundSensor::isFinished() {
    return _finished;
}

void UltrasoundSensor::_echo_isr() {
    UltrasoundSensor* _this = UltrasoundSensor::instance();

    switch (digitalRead(_this->_echo)) {
    case HIGH:
        _this->_start = micros();
        break;
    case LOW:
        _this->_end = micros();
        _this->_finished = true;
        break;
    }
}
