#ifndef _INTERRUPT_ROUTINE_H_
#define _INTERRUPT_ROUTINE_H_

class InterruptRoutine
{
    public:
        virtual void handleInterrupt() = 0;
};

#endif // _INTERRUPT_ROUTINE_H_

