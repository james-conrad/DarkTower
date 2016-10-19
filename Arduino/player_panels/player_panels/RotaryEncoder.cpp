#include "Arduino.h"

#include "RotaryEncoder.h"

#define DEBOUNCE_MILLIS 2

/**
 * Constructor
 */
RotaryEncoder::RotaryEncoder(const RotaryEncoder::Config& config)
    : _pinClock(config.pinClock)
    , _pinDirection(config.pinDirection)
    , _internalCount(0)
{
}

void RotaryEncoder::init()
{
    pinMode(_pinClock, INPUT_PULLUP);
    pinMode(_pinDirection, INPUT_PULLUP);

    _clockBounce.interval(DEBOUNCE_MILLIS);
    _clockBounce.attach(_pinClock);
}

void RotaryEncoder::resetCount()
{
    _internalCount = 0;
}

int32_t RotaryEncoder::getCount() const
{
    return _internalCount;
}

void RotaryEncoder::handleInterrupt()
{
    if (_clockBounce.update())
    {
        if (_clockBounce.rose())
        {
            if (digitalRead(_pinDirection))
            {
                _internalCount--;
            }
            else
            {
                _internalCount++;
            }
        }
    }
}
