#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

enum Signal
{
    Sig_StateEnter,
    Sig_StateExit,

    Sig_BeginTurn,
    Sig_EndTurn,
    Sig_Card,
    Sig_Button,
    Sig_Action,
    Sig_Dial,
};

class Event
{
public:
    Event(Signal _sig) : sig(_sig) {}
    virtual ~Event() {}

    Signal sig;
};

template <typename T>
class StateMachine
{
public:
    StateMachine()
      : _currentState(nullptr)
      , _exiting(false)
    {}

    typedef void (T::*StateFn)(const Event& e);

    void transitionTo(StateFn state)
    {
        if (_exiting)
        {
            //ASSERT!!!
            return;
        }

        _exiting = true;
        signal(Event(Sig_StateExit));
        _exiting = false;

        _currentState = state;
        signal(Event(Sig_StateEnter));
    }

    void signal(const Event& e)
    {
        if (_currentState)
        {
            (static_cast<T*>(this)->*_currentState)(e);
        }
    }

private:
    StateFn _currentState;
    bool _exiting;
};

#endif // _STATE_MACHINE_H_
