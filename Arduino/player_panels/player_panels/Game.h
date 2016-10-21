#ifndef _GAME_H_
#define _GAME_H_

#include "StateMachine.h"
#include "Player.h"
#include "Board.h"

enum TimeOfDay
{
    TOD_Daytime,
    TOD_Evening,
    TOD_Night,
};

static const int maxPlayers = 4;

class Game : public StateMachine<Game>
{
public:
    Game();

    void State_Init(Message m, const  char* userData);
    void State_Start(Message m, const  char* userData);
    void State_PlayerTurn(Message m, const  char* userData);
    void State_PlayerEndTurn(Message m, const  char* userData);

    Board& getBoard() { return _board; }
    void setBackground(Terrain terrain, bool road, TimeOfDay tod);
    int getMaxPlayers() { return maxPlayers; }
    Player& getPlayer(int playerId) { return _players[playerId]; }
    int getActivePlayerId() { return _activePlayerId; }

private:
    Player _players[maxPlayers];
    Board _board;
    int _activePlayerId;
};

#endif // _GAME_H_
