#ifndef _PLAYER_H_
#define _PLAYER_H_

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

class Player
{
public:
    Player();

    typedef void (Player::*StateFn)(Message m, const char* userData);
    
    void signal(Message m, const char* userData = nullptr);
    void transitionTo(StateFn state);

    void State_Wait(Message m,const  char* userData);
    void State_Turn(Message m, const char* userData);
    void State_Travel(Message m, const char* userData);
    void State_Encounter(Message m, const char* userData);

private:
    StateFn currentState;
    bool exiting;
};

#endif // _PLAYER_H_

