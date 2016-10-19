#include "Arduino.h"

#include "Player.h"

Player::Player()
    : currentState(nullptr)
    , exiting(false)
{
    transitionTo(&Player::State_Wait);
}

void Player::transitionTo(Player::StateFn state)
{
    if (exiting)
    {
        //ASSERT!!!
        return;
    }

    exiting = true;
    signal(Msg_Exit);
    exiting = false;

    currentState = state;
    signal(Msg_Enter);
}

void Player::signal(Message m, const char* userData)
{
    if (currentState)
    {
        (this->*currentState)(m, userData);
    }
}

void Player::State_Wait(Message m,const  char* userData)
{
    switch (m)
    {
        case Msg_BeginTurn:
            transitionTo(&Player::State_Turn);
            break;
    }
}

void Player::State_Turn(Message m, const char* userData)
{
    switch (m)
    {
        case Msg_Enter:
            // check the current active card.
            // is it travel?
            // transitionTo(Player::State_Travel);
            // is it explore?
            // transitionTo(Player::State_Explore);
            break;

        case Msg_CardOn:
            // check the current active card.
            // is it travel?
            // transitionTo(Player::State_Travel);
            // is it explore?
            // transitionTo(Player::State_Explore);
            break;
    }
}

void Player::State_Travel(Message m, const char* userData)
{
    switch (m)
    {
        case Msg_Dial:
            // update target location based on dial movement
            break;

        case Msg_Action:
        {
            if (strncmp(userData, "move", 5) == 0)
            {
                // move the player
                // advance time of day
                // transition to the correct state based on time remaining

            }
        }
        break;
    }
}

void Player::State_Encounter(Message m, const char* userData)
{
}
