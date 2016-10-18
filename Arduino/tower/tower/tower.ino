#include <TimerThree.h>

#include "TowerController.h"
#include "Display.h"
#include "AudioController.h"
#include "TgaImage.h"
#include "SerialCommander.h"

TowerController::Config towerConfig = {
    19, 18, 17, 16   /* Stepper Control Pins*/
};

TowerController tower(towerConfig);
Display display;
AudioController audio;
SerialCommander commander;

TgaImage image;
TgaImage image2;


void cmd_rot(const char* args)
{
    Serial1.print("Rotate: ");
    Serial1.println(args);

    if (strncmp(args, "cw", 3) == 0)
    {
        tower.cwRotate(21989 / 4);
    }

    if (strncmp(args, "ccw", 4) == 0)
    {
        tower.ccwRotate(21989 / 4);
    }
}

void cmd_snd(const char* args)
{
    Serial1.print("Sound: ");
    Serial1.println(args);

    audio.playAudio(args);
}

void cmd_bg(const char* args)
{
    Serial1.print("Background: ");
    Serial1.println(args);

    image.load(args);
    display.drawFullscreenImage(image);
}

void cmd_swap(const char* args)
{
    Serial1.println("Swap Buffers");
    display.swapBuffers();
}

void cmd_enc(const char* args)
{
    Serial1.print("Encounter: ");
    Serial1.println(args);

    display.update();
}

void cmd_text(const char* args)
{
    Serial1.print("Text: ");
    Serial1.println(args);

    display.update();
}
void setup(void)
{
    tower.init();
    display.init();
    audio.init();
    commander.init();

    commander.setCommandCallback("rot", cmd_rot);
    commander.setCommandCallback("snd", cmd_snd);
    commander.setCommandCallback("bg", cmd_bg);
    commander.setCommandCallback("enc", cmd_enc);
    commander.setCommandCallback("swap", cmd_swap);
    commander.setCommandCallback("text", cmd_text);

    Timer3.initialize(2000);
    Timer3.attachInterrupt(ISR);
    Serial.begin(9600);

    image.load("tower.tga");
    display.drawFullscreenImage(image);
    display.swapBuffers();

    audio.setAmpEnabled(false);
}

uint8_t v = 0;
void ISR()
{
    tower.handleInterrupt();
    v++;
    if (v==0)
        Serial1.print('.');
}


void loop(void)
{
    //display.setColorMap(image);

//    audio.playRandomAudio();
//    while (audio.isPlaying())
//    {
//        if (!display.drawImage(image))
//            Serial.println("draw failed");
//        else
//            Serial.print('=');   
//    }
//
//    Serial.println();   
//
//    audio.playRandomAudio();
//    while (audio.isPlaying())
//    {
//        if (!display.drawImage(image2))
//            Serial.println("draw failed");
//        else
//            Serial.print('=');
//    }
//    Serial.println();   

//    tower.update();
//

//    audio.playRandomAudio();
//    if (random(10) >= 5 )
//        tower.cwRotate(21989 / 4);
//    else
//        tower.ccwRotate(21989 / 4);
// 
//    while (!tower.movementComplete())
//    {
//        delay(100);
//        Serial.print('.');
//    }
//
//    Serial.println("*");
//    Serial.print("Move complete!\n");
//    display.update();
    commander.update();
}
