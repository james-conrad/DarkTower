#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

enum Message
{
    Msg_Enter,
    Msg_Exit,
    Msg_BeginTurn,
    Msg_CardOn,
    Msg_CardOff,
    Msg_Action,
    Msg_Dial,
};

template <typename T>
class StateMachine
{
public:
    StateMachine()
      : _currentState(nullptr)
      , _exiting(false)
    {}

    typedef void (T::*StateFn)(Message m, const char* userData);

    void transitionTo(StateFn state)
    {
        if (_exiting)
        {
            //ASSERT!!!
            return;
        }

        _exiting = true;
        signal(Msg_Exit);
        _exiting = false;

        _currentState = state;
        signal(Msg_Enter);
    }

    void signal(Message m, const char* userData = nullptr)
    {
        if (_currentState)
        {
            (static_cast<T*>(this)->*_currentState)(m, userData);
        }
    }

private:
    StateFn _currentState;
    bool _exiting;
};

#endif // _STATE_MACHINE_H_
