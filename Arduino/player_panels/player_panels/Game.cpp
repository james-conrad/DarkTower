#include "Arduino.h"

#include "Game.h"

Player::Config p1_config = {
    0xFF0000,       // color
    10,             // startingTileId
    Direction_North // startingTravelDir
};

Player::Config p2_config = {
    0x0000FF,           // color
    61,                 // startingTileId
    Direction_NorthEast // startingTravelDir
};

Player::Config p3_config = {
    0x00FF00,       // color
    83,             // startingTileId
    Direction_South // startingTravelDir
};

Player::Config p4_config = {
    0x80FF00,           // color
    32,                 // startingTileId
    Direction_SouthWest // startingTravelDir
};

Game::Game()
    : _players({
          Player(*this, p1_config),
          Player(*this, p2_config),
          Player(*this, p3_config),
          Player(*this, p4_config)
      })
    , _activePlayerId(0)
{
    transitionTo(&Game::State_Init);
}


void Game::setBackground(Terrain terrain, bool road, TimeOfDay tod)
{
    char command[100];

    if (tod == TOD_Daytime)
        Serial1.write("bg day_sky.tga\n");
    else if (tod == TOD_Evening)
        Serial1.write("bg evening_sky.tga\n");
    else
        Serial1.write("bg night_sky.tga\n");

    const char* terrain_s = "";
    const char* road_s = road ? "_road" : "";

    switch (terrain)
    {
        case Terrain_Plains:
            terrain_s = "plains";
            break;

        case Terrain_Mountains:
            terrain_s = "mountains";
            break;

        case Terrain_Swamp:
            terrain_s = "swamp";
            break;

        case Terrain_Forest:
            terrain_s = "forest";
            break;

        case Terrain_Jungle:
            terrain_s = "jungle";
            break;

        case Terrain_Desert:
            terrain_s = "desert";
            break;
    }

    snprintf(command, 100, "bg %s%s.tga\n", terrain_s, road_s);
    Serial1.write(command);
    Serial1.write("swap\n");
}


void Game::State_Init(Message m,const  char* userData)
{

}

void Game::State_Start(Message m,const  char* userData)
{

}

void Game::State_PlayerTurn(Message m,const  char* userData)
{

}

void Game::State_PlayerEndTurn(Message m,const  char* userData)
{

}
