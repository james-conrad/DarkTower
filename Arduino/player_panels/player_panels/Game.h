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

class CardEvent : public Event
{
public:
    CardEvent(int playerId, bool added)
        : Event(Sig_Card)
        , _playerId(playerId)
        , _added(added)
    {}

    int getPlayerId() const { return _playerId; }
    bool getAdded() const { return _added; }

private:
    int _playerId;
    bool _added;
};


class ButtonEvent : public Event
{
public:
    ButtonEvent(int playerId, int buttonId, bool pressed)
        : Event(Sig_Button)
        , _playerId(playerId)
        , _buttonId(buttonId)
        , _pressed(pressed)
    {}

    int getPlayerId() const { return _playerId; }
    int getButtonId() const { return _buttonId; }
    bool getPressed() const { return _pressed; }

private:
    int _playerId;
    int _buttonId;
    bool _pressed;
};

class Game : public StateMachine<Game>
{
public:
    Game();

    void State_Init(const Event& e);
    void State_Start(const Event& e);
    void State_PlayerTurn(const Event& e);
    void State_PlayerEndTurn(const Event& e);

    Board& getBoard() { return _board; }
    int getMaxPlayers() { return maxPlayers; }
    Player& getPlayer(int playerId) { return _players[playerId]; }
    int getActivePlayerId() { return _activePlayerId; }
    bool isPlaying(int playerId) { return _isPlaying[playerId]; }

    void setBackground(Terrain terrain, bool road, TimeOfDay tod);
    void playSound(const char* sound);

private:
    Player _players[maxPlayers];
    bool _isPlaying[maxPlayers];
    Board _board;
    int _activePlayerId;
};

#endif // _GAME_H_
