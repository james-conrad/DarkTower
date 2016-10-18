#include <Audio.h>
#include <SPI.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=696,344
AudioOutputAnalog        dac1;           //xy=988,382
AudioConnection          patchCord1(sine1, dac1);
// GUItool: end automatically generated code


const int FlashChipSelect = 28;

void setup()
{
    while (!Serial);

    if (!SerialFlash.begin(FlashChipSelect))
        Serial.println("Unable to acccess SerialFlash chip");

    AudioMemory(20);
    dac1.analogReference(EXTERNAL); // much louder!
    delay(50);             // time for DAC voltage stable
    pinMode(26, OUTPUT);
    digitalWrite(26, HIGH); // turn on the amplifier

    delay(10);             // allow time to wake up

    SerialFlashFile file;
    file = SerialFlash.open("D01.RAW");
    if (file) {  // true if the file exists
        Serial.println("D02.RAW");
        Serial.println(file.size());
    }

    //playFlashRaw1.play("D02.RAW");

    sine1.frequency(400);
    sine1.amplitude(1);
}

void loop()
{
    //while (tonesweep1.isPlaying());

    //tonesweep1.play(1, 200, 600, 2000);
}

