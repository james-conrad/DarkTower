#ifndef _AUDIO_CONTROLLER_H_
#define _AUDIO_CONTROLLER_H_

class AudioController
{
public:
    AudioController();

    void init();
    void update();
    void playAudio(const char* filename);
    void playRandomAudio();
    bool isPlaying();

    void setAmpEnabled(bool enabled);
    bool isAmpEnabled();

private:
    bool _ampEnabled;
};

#endif // _AUDIO_CONTROLLER_H_
