#ifndef _TOWER_CONTROLLER_H_
#define _TOWER_CONTROLLER_H_

#include "InterruptRoutine.h"

class TowerController : public InterruptRoutine
{
public:
    struct Config
    {
        int pinMotor1;
        int pinMotor2;
        int pinMotor3;
        int pinMotor4;
    };

    TowerController(const Config& config);

    void init();
    void update();
    bool movementComplete();
    void cwRotate(int64_t steps);
    void ccwRotate(int64_t steps);

    /*
     * InterruptRoutine Implementation
     */
    virtual void handleInterrupt();

protected:
    int _pinMotor1;
    int _pinMotor2;
    int _pinMotor3;
    int _pinMotor4;

    bool _movementComplete;

    volatile int64_t _steps;
    volatile int64_t _desiredSteps;
};

#endif // _TOWER_CONTROLLER_H_
