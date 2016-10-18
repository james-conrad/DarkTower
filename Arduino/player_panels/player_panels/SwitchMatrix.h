#ifndef _SWITCH_MATRIX_H_
#define _SWITCH_MATRIX_H_

#include "InterruptRoutine.h"

class SwitchMatrix : public InterruptRoutine
{
public:
    struct Config
    {
        uint8_t numRows;
        int* rowPins;
        uint8_t numColumns;
        int* columnPins;
    };

    SwitchMatrix(const Config& config);

    void init();
    void update();
    bool buttonDown(int buttonIndex);
    bool buttonPressed(int buttonIndex);
    bool buttonReleased(int buttonIndex);

    /*
     * InterruptRoutine Implementation
     */
    virtual void handleInterrupt();

protected:
    void _advanceRowAddress();

    uint8_t _numRows;
    uint8_t _numColumns;
    int* _rowPins;
    int* _columnPins;

    uint32_t _buttonDown;
    uint32_t _buttonPressed;
    uint32_t _buttonReleased;

    volatile uint32_t _buttonState;
    uint8_t _buttonHistory[32];
    uint8_t _historyIndex;
    uint8_t _rowIndex;
};

#endif // _SWITCH_MATRIX_H_

