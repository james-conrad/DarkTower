#include "Arduino.h"

#include "AudioController.h"

#include <Audio.h>
#include <SerialFlash.h>

#define MEM_CS  28
#define AMP_EN  26

// GUItool: begin automatically generated code
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=734,383
AudioOutputAnalog        dac1;           //xy=988,382
AudioConnection          patchCord1(playFlashRaw1, dac1);
// GUItool: end automatically generated code

AudioController::AudioController()
    : _ampEnabled(true)
{}

void AudioController::init()
{
    if (!SerialFlash.begin(MEM_CS))
        Serial.println("Unable to acccess SerialFlash chip");

    AudioMemory(20);
    dac1.analogReference(EXTERNAL); // much louder!
    delay(50);             // time for DAC voltage stable
    pinMode(AMP_EN, OUTPUT);
    digitalWrite(AMP_EN, HIGH); // turn on the amplifier

    pinMode(27, OUTPUT);
    digitalWrite(27, LOW); // turn off LED

    delay(10);             // allow time to wake up}
}

bool AudioController::isAmpEnabled()
{
    return _ampEnabled;
}

void AudioController::setAmpEnabled(bool enabled)
{
    _ampEnabled = enabled;
    digitalWrite(AMP_EN, enabled);

    if (enabled)
    {
        delay(10);             // allow time to wake up}
    }
}

void AudioController::update()
{
}

void AudioController::playAudio(const char* filename)
{
    if (!_ampEnabled)
        setAmpEnabled(true);

    playFlashRaw1.play(filename);
}

void AudioController::playRandomAudio()
{
    int r = random(7);
    const char* filename = "success.raw";

    switch (r)
    {
        case 0:
            filename = "achieve.raw";
            break;

        case 1:
            filename = "ding.raw";
            break;

        case 2:
            filename = "door.raw";
            break;

        case 3:
            filename = "dragon.raw";
            break;

        case 4:
            filename = "lose.raw";
            break;

        case 5:
            filename = "success.raw";
            break;

        case 6:
            filename = "win.raw";
            break;
    }

    playFlashRaw1.play(filename);
}

bool AudioController::isPlaying()
{
    return playFlashRaw1.isPlaying();
}

