#include <Audio.h>
#include <SPI.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=734,383
AudioOutputAnalog        dac1;           //xy=988,382
AudioConnection          patchCord1(playFlashRaw1, dac1);
// GUItool: end automatically generated code

const int FlashChipSelect = 28;
const int AmpEnable = 26;

//const int FlashChipSelect = 6;
//const int AmpEnable = 5;

void setup()
{
    if (!SerialFlash.begin(FlashChipSelect))
        Serial.println("Unable to acccess SerialFlash chip");

    AudioMemory(20);
    dac1.analogReference(EXTERNAL); // much louder!
    delay(50);             // time for DAC voltage stable
    pinMode(AmpEnable, OUTPUT);
    digitalWrite(AmpEnable, HIGH); // turn on the amplifier

    pinMode(27, OUTPUT);
    digitalWrite(27, LOW); // turn off LED

    delay(10);             // allow time to wake up

    SerialFlashFile file;
    file = SerialFlash.open("D01.RAW");
    if (file) {  // true if the file exists
        Serial.println("D02.RAW");
        Serial.println(file.size());
    }

    playFlashRaw1.play("D02.RAW");
}

void loop()
{
    while (playFlashRaw1.isPlaying());

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

