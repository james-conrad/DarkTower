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
    , _tod(TOD_Daytime)
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

void Player::State_Wait(const Event& e)
{
    switch (e.sig)
    {
        case Sig_BeginTurn:
            transitionTo(&Player::State_Turn);
            break;
    }
}

void Player::State_Turn(const Event& e)
{
    switch (e.sig)
    {
        case Sig_StateEnter:
        {
            Tile& tile = *_game.getBoard().getTile(_tileId);
            _tod = TOD_Daytime;
            _game.setBackground(tile.terrain, _game.getBoard().hasRoad(_tileId), _tod);
            // check the current active card.
            // is it travel?
            // transitionTo(Player::State_Travel);
            // is it explore?
            // transitionTo(Player::State_Explore);
        }
        break;

        case Sig_Card:
            // check the current active card.
            // is it travel?
            // transitionTo(Player::State_Travel);
            // is it explore?
            // transitionTo(Player::State_Explore);
            break;

        case Sig_Dial:
        {
            const DialEvent& de = *static_cast<const DialEvent*>(&e);
            Tile& tile = *_game.getBoard().getTile(_tileId);
            if (de.getDialChange() > 0)
            {
                do
                {
                    _travelDir = clockwise(_travelDir);
                    _destinationTileId = tile.adjacent_id[_travelDir];
                }
                while (_destinationTileId == -1);
            }
            else
            {
                do
                {
                    _travelDir = counter_clockwise(_travelDir);
                    _destinationTileId = tile.adjacent_id[_travelDir];
                }
                while (_destinationTileId == -1);
            }
        }
        break;

        case Sig_Button:
        {
            const ButtonEvent& be = *static_cast<const ButtonEvent*>(&e);
            if (be.getButtonId() == 1 && be.getPressed() == false)
            {
                transitionTo(&Player::State_EndTurn);
            }

            if (be.getButtonId() == 0 && be.getPressed() == false)
            {
                if (_tod == TOD_Night)
                {
                    _game.playSound("lose");
                }
                else
                {
                    _game.playSound("achieve");
                    _tod = _tod == TOD_Daytime ? TOD_Evening : TOD_Night;

                    _tileId = _destinationTileId;

                    Tile& tile = *_game.getBoard().getTile(_tileId);
                    _destinationTileId = tile.adjacent_id[_travelDir];

                    while (_destinationTileId == -1)
                    {
                        _travelDir = clockwise(_travelDir);
                        _destinationTileId = tile.adjacent_id[_travelDir];
                    }

                    _game.setBackground(tile.terrain, _game.getBoard().hasRoad(_tileId), _tod);
                }
            }
        }
        break;
    }
}

void Player::State_EndTurn(const Event& e)
{
    switch (e.sig)
    {
        case Sig_StateEnter:
            transitionTo(&Player::State_Wait);
            _game.signal(Event(Sig_EndTurn));
            break;
    }
}

void Player::State_Travel(const Event& e)
{
    switch (e.sig)
    {
        case Sig_Dial:
            // update target location based on dial movement
            break;

        case Sig_Action:
        {
            //if (strncmp(userData, "move", 5) == 0)
            {
                // move the player
                // advance time of day
                // transition to the correct state based on time remaining

            }
        }
        break;
    }
}

void Player::State_Encounter(const Event& e)
{
}
