#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "StateMachine.h"
#include "Board.h"

class Game;

class Player : public StateMachine<Player>
{
public:
    struct Config
    {
        uint32_t color;
        int startingTileId;
        Direction startingTravelDir;
    };

    Player(Game& game, const Config& config);
    int getTileId() { return _tileId; }
    int getDestinationTileId() { return _destinationTileId; }
    uint32_t getColor() { return _color; }

private:
    void State_Wait(const Event& e);
    void State_Turn(const Event& e);
    void State_Travel(const Event& e);
    void State_Encounter(const Event& e);

    Game& _game;

    uint32_t _color;
    int _tileId;
    Direction _travelDir;
    int _destinationTileId;
};

#endif // _PLAYER_H_
