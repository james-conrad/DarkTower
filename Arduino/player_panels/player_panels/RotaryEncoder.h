#ifndef _ROTARY_ENCODER_H_
#define _ROTARY_ENCODER_H_

#include "InterruptRoutine.h"
#include <Bounce2.h>

class RotaryEncoder : public InterruptRoutine
{
public:
    struct Config
    {
        int pinClock;
        int pinDirection;
    };

    RotaryEncoder(const Config& config);

    void init();

    virtual void handleInterrupt();

    void resetCount();
    int32_t getCount() const;

private:
    int _pinClock;
    int _pinDirection;

    int32_t _internalCount;

    Bounce _clockBounce;
};

#endif // _ROTARY_ENCODER_H_
