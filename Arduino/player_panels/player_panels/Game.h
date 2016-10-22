#ifndef _GAME_H_
#define _GAME_H_

#include "StateMachine.h"
#include "Player.h"
#include "Board.h"
#include "TimeOfDay.h"

static const int maxPlayers = 4;

class PlayerEvent : public Event
{
public:
    PlayerEvent(Signal sig, int playerId)
      : Event(sig)
      , _playerId(playerId)
    {}

    int getPlayerId() const { return _playerId; }

private:
    int _playerId;
};

class CardEvent : public PlayerEvent
{
public:
    CardEvent(int playerId, bool added)
        : PlayerEvent(Sig_Card, playerId)
        , _added(added)
    {}

    bool getAdded() const { return _added; }

private:
    bool _added;
};


class ButtonEvent : public PlayerEvent
{
public:
    ButtonEvent(int playerId, int buttonId, bool pressed)
        : PlayerEvent(Sig_Button, playerId)
        , _buttonId(buttonId)
        , _pressed(pressed)
    {}

    int getButtonId() const { return _buttonId; }
    bool getPressed() const { return _pressed; }

private:
    int _buttonId;
    bool _pressed;
};


class DialEvent : public PlayerEvent
{
public:
    DialEvent(int playerId, int dialChange)
        : PlayerEvent(Sig_Dial, playerId)
        , _dialChange(dialChange)
    {}

    int getDialChange() const { return _dialChange; }

private:
    int _dialChange;
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
    void turnTower();

private:
    Player _players[maxPlayers];
    bool _isPlaying[maxPlayers];
    Board _board;
    int _activePlayerId;
};

#endif // _GAME_H_
