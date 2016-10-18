#ifndef _GAME_H_
#define _GAME_H_

class Game
{
public:
    Game();

    void init(int numPlayers, GameController* controller);

private:
    GameController* _controller;
    int _numPlayers;
};

#endif // _GAME_H_
