#include "UltrasoundSensor.h"
#include "Arduino.h"

enum SensorPhase {
    TRIGGER = 1, 
    SENDING = 2, 
    RECIEVE = 3
};

UltrasoundSensor* UltrasoundSensor::_instance(NULL);

UltrasoundSensor::UltrasoundSensor(int trigger, int echo, int max_dist)
    : _trigger(trigger), _echo(echo), _max(max_dist * 58)
{
    if (_instance == 0) _instance = this;
}

void UltrasoundSensor::init()
{
    pinMode(_trigger, OUTPUT);
    pinMode(_echo, INPUT);
}

void UltrasoundSensor::onLoop()
{
    switch (_phase)
    {
    case TRIGGER: {
        digitalWrite(_trigger, HIGH);
        delayMicroseconds(10);
        digitalWrite(_trigger, LOW);
        _phase = SENDING;
        break;
    }
    case SENDING: {
        if (digitalRead(_echo) == HIGH) {
            _phaseTime = micros();
            _phase = RECIEVE;
        }
        // Exit if pings are not sent fast enough
        else if ((micros() - _phase) > 500UL) {
            Serial.println("Error1: Ping not sent");
            _phase = TRIGGER;
        }
        break;
    }
    case RECIEVE: {
        // Exit if no echo is received (e.g. because too far away)
        if ((micros() - _phaseTime) > 20000UL) {
            Serial.println("Error2: No echo received");
            _phase = TRIGGER;
        }
        else if (digitalRead(_echo) == LOW) {
            _pulseTime = (micros() - _phaseTime);
            _phase = TRIGGER;
        }
        break;
    }
    default:
        break;
    }
}

unsigned int UltrasoundSensor::measure()
{
    digitalWrite(_trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigger, LOW);
    const unsigned int measured = pulseIn(_echo, HIGH, _max) / 58;
    if (measured == 0) return _max;

    return measured;
}

unsigned int UltrasoundSensor::getRange()
{
    return _pulseTime / 58.2;
}
