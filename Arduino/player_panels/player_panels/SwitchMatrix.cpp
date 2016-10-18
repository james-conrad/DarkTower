#include "Arduino.h"

#include "SwitchMatrix.h"

/**
 * Constructor
 */
SwitchMatrix::SwitchMatrix(const SwitchMatrix::Config& config)
    : _numRows(config.numRows)
    , _numColumns(config.numColumns)
    , _rowPins(config.rowPins)
    , _columnPins(config.columnPins)
    , _buttonDown(0)
    , _buttonPressed(0)
    , _buttonReleased(0)
    , _buttonState(0)
    , _buttonHistory()
    , _historyIndex(0)
    , _rowIndex(0)
{
    memset(_buttonHistory, 0, sizeof(_buttonHistory));
}

void SwitchMatrix::init()
{
    for (int iRow = 0; iRow < _numRows; ++iRow)
    {
        pinMode(_rowPins[iRow], OUTPUT);
        digitalWrite(_rowPins[iRow], LOW);
    }

    for (int iCol = 0; iCol < _numColumns; ++iCol)
    {
        pinMode(_columnPins[iCol], INPUT_PULLUP);
    }
}

void SwitchMatrix::update()
{
    /*
     * Disable interrupts while we copy out volatile button state
     */
    noInterrupts();
    uint32_t newButtonDown = _buttonState;
    interrupts();

    _buttonPressed = newButtonDown & ~_buttonDown;
    _buttonReleased = _buttonDown & ~newButtonDown;
    _buttonDown = newButtonDown;
}

bool SwitchMatrix::buttonDown(int buttonIndex)
{
    return (_buttonDown >> buttonIndex) & 0x0001;
}

bool SwitchMatrix::buttonPressed(int buttonIndex)
{
    return (_buttonPressed >> buttonIndex) & 0x0001;
}

bool SwitchMatrix::buttonReleased(int buttonIndex)
{
    return (_buttonReleased >> buttonIndex) & 0x0001;
}

void SwitchMatrix::handleInterrupt()
{
    int buttonIndex = _rowIndex * _numColumns;
    uint8_t* history = &_buttonHistory[buttonIndex];

    uint8_t downMask = 1 << _historyIndex;
    uint8_t upMask = ~downMask;

    for (int iCol = 0; iCol < _numColumns; ++iCol)
    {
        int pinValue = digitalRead(_columnPins[iCol]);

        if (!pinValue)
        {
            *history |= downMask;
        }
        else
        {
            *history &= upMask;
        }

        /*
         * Detect 8 consecutive reads of 0 or 1 for this
         * button, and update _buttonState accordingly
         */
        if (*history == 0x00)
        {
            _buttonState &= ~(1 << buttonIndex);
        }
        else if (*history == 0xff)
        {
            _buttonState |= 1 << buttonIndex;
        }
        
        history++;
        buttonIndex++;
    }

    _advanceRowAddress();

    /*
     * If we've advanced back to the first row, increment
     * the history index.
     */
    if (_rowIndex == 0)
    {
        _historyIndex += 1;
        _historyIndex &= 0x7;
    }
}

void SwitchMatrix::_advanceRowAddress()
{
    _rowIndex += 1;
    if (_rowIndex > _numRows)
    {
        _rowIndex = 0;
    }

    for (int iRow = 0; iRow < _numRows; ++iRow)
    {
        digitalWrite(_rowPins[iRow], _rowIndex != iRow);
    }
}

