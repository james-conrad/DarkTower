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
};

#endif // _AUDIO_CONTROLLER_H_
