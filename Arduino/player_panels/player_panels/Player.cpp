#include "Arduino.h"

#include "Player.h"
#include "Game.h"

Player::Player(Game& game, const Player::Config& config)
    : StateMachine()
    , _game(game)
    , _color(config.color)
    , _tileId(config.startingTileId)
    , _travelDir(config.startingTravelDir)
    , _destinationTileId(-1)
{
    transitionTo(&Player::State_Wait);

    Tile& tile = *game.getBoard().getTile(_tileId);
    _destinationTileId = tile.adjacent_id[_travelDir];

    while (_destinationTileId == -1)
    {
        _travelDir = clockwise(_travelDir);
        _destinationTileId = tile.adjacent_id[_travelDir];
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
