#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>

#include "AnsiTerm.h"
#include "SwitchMatrix.h"
#include "RotaryEncoder.h"
#include "CardInterface.h"
#include "Board.h"

SwitchMatrix::Config matrixConfig =
{
    8, /* Number of Rows */
    (int[]){4, 5, 6, 24, 25, 26, 27, 28}, /* Row pins */
    3, /* Number of Columns */
    (int[]){23, 22, 21} /* Column Return Pins */
};

SwitchMatrix matrix(matrixConfig);

RotaryEncoder::Config encoderConfig =
{
    19, /* Clock Pin */
    20  /* Direction  Pin */
};

RotaryEncoder encoder(encoderConfig);

RotaryEncoder::Config encoderConfig2 =
{
    17, /* Clock Pin */
    18  /* Direction  Pin */
};

RotaryEncoder encoder2(encoderConfig2);

RotaryEncoder::Config encoderConfig3 =
{
    15, /* Clock Pin */
    16  /* Direction  Pin */
};

RotaryEncoder encoder3(encoderConfig3);

RotaryEncoder::Config encoderConfig4 =
{
    3, /* Clock Pin */
    2  /* Direction  Pin */
};

RotaryEncoder encoder4(encoderConfig4);


CardInterface::Config cardConfig =
{
    10 /* Chip Select pin */  
};

CardInterface card(cardConfig);

CardInterface::Config cardConfig2 =
{
    9 /* Chip Select pin */  
};

CardInterface card2(cardConfig2);

CardInterface::Config cardConfig3 =
{
    8 /* Chip Select pin */  
};

CardInterface card3(cardConfig3);

CardInterface::Config cardConfig4 =
{
    7 /* Chip Select pin */  
};

CardInterface card4(cardConfig4);

AnsiTerm term(Serial);

#define LED_PIN 14
Adafruit_NeoPixel strip = Adafruit_NeoPixel(186, LED_PIN, NEO_GRB + NEO_KHZ800);

Direction travel_dir = Direction_North;
int tileId = 10;
int destination_id = tiles[tileId].adjacent_id[travel_dir];
uint8_t locations[num_tiles];

void setup(void)
{
    matrix.init();
    encoder.init();
    encoder2.init();
    encoder3.init();
    encoder4.init();

    // disable all SPI devices before init.
    digitalWrite(cardConfig.chipSelectPin, HIGH);
    digitalWrite(cardConfig2.chipSelectPin, HIGH);
    digitalWrite(cardConfig3.chipSelectPin, HIGH);
    digitalWrite(cardConfig4.chipSelectPin, HIGH);
    
    card.init();
    card2.init();
    card3.init();
    card4.init();

    Timer1.initialize(20000 / 64);
    Timer1.attachInterrupt(ISR);

    Serial.begin(9600);
    Serial1.begin(38400);
 
    term.clearAll();

    strip.begin();
    strip.show();

    for (int i = 0; i < num_tiles; ++i)
    {
        locations[i] = random(0, 36);
    }

    setBackground(locations[tileId]);
}

void setBackground(uint8_t location)
{
    char command[100];

    if (location < 12)
        Serial1.write("bg day_sky.tga\n");
    else if (location < 24)
        Serial1.write("bg evening_sky.tga\n");
    else
        Serial1.write("bg night_sky.tga\n");

    uint8_t loc1 = location % 12;

    const char* terrain = "";
    const char* road = loc1 >= 6 ? "_road" : "";

    switch (loc1 % 6)
    {
        case 0:
            terrain = "plains";
            break;

        case 1:
            terrain = "mountains";
            break;

        case 2:
            terrain = "swamp";
            break;

        case 3:
            terrain = "forest";
            break;

        case 4:
            terrain = "jungle";
            break;

        case 5:
            terrain = "desert";
            break;
    }

    snprintf(command, 100, "bg %s%s.tga\n", terrain, road);
    Serial1.write(command);
    Serial1.write("swap\n");
}

uint32_t terrain_colors[Terrain_Count] = {
    0x304000, // Terrain_Plains 
    0xffff00, // Terrain_Desert,
    0x1122bb, // Terrain_Mountain,
    0x3300ff, // Terrain_Swamp,
    0x00ff00, // Terrain_Forest,
};



uint8_t j = 0;
uint8_t t = 0;

void ISR()
{
    matrix.handleInterrupt();
    encoder.handleInterrupt();
    encoder2.handleInterrupt();
    encoder3.handleInterrupt();
    encoder4.handleInterrupt();
 
    t++;
    if (t > 30)
    {
        t = 0;
        
        for(int i = 0; i< num_tiles; i++)
        {
            Tile& tile = tiles[i];
            uint32_t c = terrain_colors[tile.terrain];
            if (i == tileId)
                c = 0xffffff;
            if (i == destination_id)
                c = 0x00ffff;

            for (int l = tile.led_index; l < tile.led_index + tile.led_count; ++l)
            {
                strip.setPixelColor(l, c);
            }
        }

        strip.show();
    }
}

int32_t lastEncoderValue = 0;
int32_t lastEncoderValue2 = 0;
int32_t lastEncoderValue3 = 0;
int32_t lastEncoderValue4 = 0;

void loop(void)
{
    matrix.update();

    for (int button = 0; button < 32; ++button)
    {
        if (matrix.buttonPressed(button))
        {
            term.attr(AnsiTerm::BOLD);
            term.print("Button pressed: ");
            term.println(button);
            term.attr();
        }
        if (matrix.buttonReleased(button))
        {
            term.attr(AnsiTerm::BOLD, AnsiTerm::BG_Red, AnsiTerm::FG_Cyan);
            term.print("Button released: ");
            term.print(button);
            term.attr();
            term.println();
        }
    }

    if (matrix.buttonPressed(0))
    {
        do
        {
            travel_dir = clockwise(travel_dir);
            destination_id = tiles[tileId].adjacent_id[travel_dir];
        }
        while (destination_id == -1);
    }

    if (matrix.buttonPressed(2))
    {
        if (destination_id != -1)
        {
            tileId = destination_id;
            destination_id = tiles[tileId].adjacent_id[travel_dir];

            setBackground(locations[tileId]);

            while (destination_id == -1)
            {
                travel_dir = clockwise(travel_dir);
                destination_id = tiles[tileId].adjacent_id[travel_dir];
            }
        }
    }

    int32_t newEncoderValue = encoder.getCount();

    if (lastEncoderValue != newEncoderValue)
    {
        if (newEncoderValue > lastEncoderValue)
        {
            do
            {
                travel_dir = clockwise(travel_dir);
                destination_id = tiles[tileId].adjacent_id[travel_dir];
            }
            while (destination_id == -1);
        }
        else
        {
             do
            {
                travel_dir = counter_clockwise(travel_dir);
                destination_id = tiles[tileId].adjacent_id[travel_dir];
            }
            while (destination_id == -1);       
        }

        term.attr(AnsiTerm::FG_Red);
        term.print("Encoder: ");
        term.println(newEncoderValue);
        term.attr();
        lastEncoderValue = newEncoderValue;
    }

    int32_t newEncoderValue2 = encoder2.getCount();

    if (lastEncoderValue2 != newEncoderValue2)
    {
        term.attr(AnsiTerm::FG_Blue);
        term.print("Encoder: ");
        term.println(newEncoderValue2);
        term.attr();
        lastEncoderValue2 = newEncoderValue2;

    }
 
    int32_t newEncoderValue3 = encoder3.getCount();

    if (lastEncoderValue3 != newEncoderValue3)
    {
        term.attr(AnsiTerm::FG_Green);
        term.print("Encoder: ");
        term.println(newEncoderValue3);
        term.attr();
        lastEncoderValue3 = newEncoderValue3;

    }
    int32_t newEncoderValue4 = encoder4.getCount();

    if (lastEncoderValue4 != newEncoderValue4)
    {
        term.attr(AnsiTerm::FG_Yellow);
        term.print("Encoder: ");
        term.println(newEncoderValue4);
        term.attr();
        lastEncoderValue4 = newEncoderValue4;

    }

    static uint32_t previousCard = 0;

    //card.scan();

    if (card.getUid() != previousCard)
    {
        previousCard = card.getUid();

        if (previousCard == 0)
        {
            term.attr(AnsiTerm::FG_Red);
            term.println("Card removed.");
            term.attr();

        }
        else
        {
            term.attr(AnsiTerm::FG_Red, AnsiTerm::BOLD);
            term.print("Card scan: ");
            term.println(card.getUid());
            term.attr();
        }
    }
    static uint32_t previousCard2 = 0;

    //card2.scan();

    if (card2.getUid() != previousCard2)
    {
        previousCard2 = card2.getUid();

        if (previousCard2 == 0)
        {
            term.attr(AnsiTerm::FG_Blue);
            term.println("Card removed.");
            term.attr();

        }
        else
        {
            term.attr(AnsiTerm::FG_Blue, AnsiTerm::BOLD);
            term.print("Card scan: ");
            term.println(card2.getUid());
            term.attr();
        }
    }
    static uint32_t previousCard3 = 0;

    //card3.scan();

    if (card3.getUid() != previousCard3)
    {
        previousCard3 = card3.getUid();

        if (previousCard3 == 0)
        {
            term.attr(AnsiTerm::FG_Green);
            term.println("Card removed.");
            term.attr();

        }
        else
        {
            term.attr(AnsiTerm::FG_Green, AnsiTerm::BOLD);
            term.print("Card scan: ");
            term.println(card3.getUid());
            term.attr();
        }
    }
    
    static uint32_t previousCard4 = 0;

    //card4.scan();

    if (card4.getUid() != previousCard4)
    {
        previousCard4 = card4.getUid();

        if (previousCard4 == 0)
        {
            term.attr(AnsiTerm::FG_Yellow);
            term.println("Card removed.");
            term.attr();

        }
        else
        {
            term.attr(AnsiTerm::FG_Yellow, AnsiTerm::BOLD);
            term.print("Card scan: ");
            term.println(card4.getUid());
            term.attr();
        }
    }

    int incomingByte;

    while (Serial1.available() > 0) {
        incomingByte = Serial1.read();
        Serial.write(incomingByte);
    }

    while (Serial.available() > 0) {
        incomingByte = Serial.read();
        Serial1.write(incomingByte);
        // local echo
        Serial.write(incomingByte);
    }
}


