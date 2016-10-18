#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

class GameController
{
public:
    GameController(Stream* towerConnection);

    void moveTower(int playerPosition);
    bool isTowerMoving();
    int getTargetTowerPosition();

    void illuminatePosition(int boardPosition, RGB color);
    void clearIllumination();

    void playAudio(const char* audioFile);
    bool isAudioPlaying();
};

#endif // _GAME_CONTROLLER_H_
