#include "Arduino.h"

#include "TowerController.h"

/**
 * Constructor
 */
TowerController::TowerController(const TowerController::Config& config)
    : _pinMotor1(config.pinMotor1)
    , _pinMotor2(config.pinMotor2)
    , _pinMotor3(config.pinMotor3)
    , _pinMotor4(config.pinMotor4)
    , _movementComplete(true)
    , _steps(0)
    , _desiredSteps(0)
{
}

void TowerController::init()
{
    pinMode(_pinMotor1, OUTPUT);
    pinMode(_pinMotor2, OUTPUT);
    pinMode(_pinMotor3, OUTPUT);
    pinMode(_pinMotor4, OUTPUT);
}

void TowerController::update()
{
}

bool TowerController::movementComplete()
{
    /*
     * Disable interrupts while we compare volatile state
     */
    noInterrupts();
    bool complete = _steps == _desiredSteps;
    interrupts();

    return complete;
}

void TowerController::handleInterrupt()
{
    if (_desiredSteps > _steps)
    {
        _steps ++;
    }
    else if (_desiredSteps < _steps)
    {
        _steps --;
    }
    else
    {
        /*
         * Movement is complete, nothing to do.
         */
        return;
    }

    int phase = _steps & 0x07;
    
    switch (phase)
    {
        case 0:
            digitalWrite(_pinMotor1, HIGH);
            digitalWrite(_pinMotor2, LOW);
            digitalWrite(_pinMotor3, LOW);
            digitalWrite(_pinMotor4, LOW);
            break;
        
        case 1:
            digitalWrite(_pinMotor1, HIGH);
            digitalWrite(_pinMotor2, HIGH);
            digitalWrite(_pinMotor3, LOW);
            digitalWrite(_pinMotor4, LOW);
            break;
        
        case 2:
            digitalWrite(_pinMotor1, LOW);
            digitalWrite(_pinMotor2, HIGH);
            digitalWrite(_pinMotor3, LOW);
            digitalWrite(_pinMotor4, LOW);
            break;
        
        case 3:
            digitalWrite(_pinMotor1, LOW);
            digitalWrite(_pinMotor2, HIGH);
            digitalWrite(_pinMotor3, HIGH);
            digitalWrite(_pinMotor4, LOW);
            break;
        
        case 4:
            digitalWrite(_pinMotor1, LOW);
            digitalWrite(_pinMotor2, LOW);
            digitalWrite(_pinMotor3, HIGH);
            digitalWrite(_pinMotor4, LOW);
            break;
        
        case 5:
            digitalWrite(_pinMotor1, LOW);
            digitalWrite(_pinMotor2, LOW);
            digitalWrite(_pinMotor3, HIGH);
            digitalWrite(_pinMotor4, HIGH);
            break;
        
        case 6:
            digitalWrite(_pinMotor1, LOW);
            digitalWrite(_pinMotor2, LOW);
            digitalWrite(_pinMotor3, LOW);
            digitalWrite(_pinMotor4, HIGH);
            break;
        
        
        case 7:
            digitalWrite(_pinMotor1, HIGH);
            digitalWrite(_pinMotor2, LOW);
            digitalWrite(_pinMotor3, LOW);
            digitalWrite(_pinMotor4, HIGH);
            break;
        }
}

void TowerController::cwRotate(int64_t steps)
{
    _desiredSteps += steps;
}

void TowerController::ccwRotate(int64_t steps)
{
    _desiredSteps -= steps;
}

