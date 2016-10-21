#include <TimerOne.h>
#include <Adafruit_NeoPixel.h>

#include "AnsiTerm.h"
#include "SwitchMatrix.h"
#include "RotaryEncoder.h"
#include "CardInterface.h"
#include "Game.h"

SwitchMatrix::Config matrixConfig =
{
    8, /* Number of Rows */
    (int[]){4, 5, 6, 24, 25, 26, 27, 28}, /* Row pins */
    3, /* Number of Columns */
    (int[]){23, 22, 21} /* Column Return Pins */
};

SwitchMatrix matrix(matrixConfig);

RotaryEncoder::Config encoderConfig1 =
{
    19, /* Clock Pin */
    20  /* Direction  Pin */
};

RotaryEncoder encoder1(encoderConfig1);

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


CardInterface::Config cardConfig1 =
{
    10 /* Chip Select pin */
};

CardInterface card1(cardConfig1);

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

Game game;

#define LED_PIN 14
Adafruit_NeoPixel strip = Adafruit_NeoPixel(186, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup(void)
{
    matrix.init();
    encoder1.init();
    encoder2.init();
    encoder3.init();
    encoder4.init();

    // disable all SPI devices before init.
    digitalWrite(cardConfig1.chipSelectPin, HIGH);
    digitalWrite(cardConfig2.chipSelectPin, HIGH);
    digitalWrite(cardConfig3.chipSelectPin, HIGH);
    digitalWrite(cardConfig4.chipSelectPin, HIGH);

    card1.init();
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
}

#define rgb(r, g, b) (uint32_t)(r << 16 | g << 8 | b)
uint32_t terrain_colors[Terrain_Count] = {
    rgb(100, 255, 200),  // Terrain_Plains
    rgb(255, 190, 0), // Terrain_Desert,
    rgb(15, 25, 40), // Terrain_Mountain,
    rgb(40, 0, 128),    // Terrain_Swamp,
    rgb(40, 255, 90),    // Terrain_Forest,
    rgb(20, 60, 0),     // Terrain_Jungle,
};

uint8_t j = 0;
uint8_t t = 0;
uint16_t counter = 0;

void ISR()
{
    matrix.handleInterrupt();
    encoder1.handleInterrupt();
    encoder2.handleInterrupt();
    encoder3.handleInterrupt();
    encoder4.handleInterrupt();

    t++;
    counter++;
    if (t > 30)
    {
        t = 0;

        Board& board = game.getBoard();

        for(int i = 0; i < num_tiles; i++)
        {
            Tile& tile = *board.getTile(i);
            uint32_t c = terrain_colors[tile.terrain];

            for (int l = tile.led_index; l < tile.led_index + tile.led_count; ++l)
            {
                strip.setPixelColor(l, c);
            }
        }

        for (int i = 0; i < game.getMaxPlayers(); ++i)
        {
            if (!game.isPlaying(i))
                continue;

            Player& p = game.getPlayer(i);
            Tile& playerTile = *board.getTile(p.getTileId());
            uint32_t c = p.getColor();

            for (int l = playerTile.led_index; l < playerTile.led_index + playerTile.led_count; ++l)
            {
                strip.setPixelColor(l, c);
            }

            if (counter > 250 && i == game.getActivePlayerId())
            {
                Tile& destinationTile = *board.getTile(p.getDestinationTileId());
                for (int l = destinationTile.led_index; l < destinationTile.led_index + destinationTile.led_count; ++l)
                {
                    strip.setPixelColor(l, 0xA0FFFF);
                }
            }
        }

        if (counter > 750)
          counter = 0;

        strip.show();
    }
}

int32_t lastEncoderValue1 = 0;
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

            int playerId = button / 6;
            int buttonId = button % 6;
            game.signal(ButtonEvent(playerId, buttonId, true));
        }
        if (matrix.buttonReleased(button))
        {
            term.attr(AnsiTerm::BOLD, AnsiTerm::BG_Red, AnsiTerm::FG_Cyan);
            term.print("Button released: ");
            term.print(button);
            term.attr();
            term.println();

            int playerId = button / 6;
            int buttonId = button % 6;
            game.signal(ButtonEvent(playerId, buttonId, false));
        }
    }

    // if (matrix.buttonPressed(2))
    // {
    //     if (destination_id != -1)
    //     {
    //         tileId = destination_id;
    //         destination_id = tiles[tileId].adjacent_id[travel_dir];
    //
    //         setBackground(tiles[tileId].terrain, false, TOD_Evening);
    //
    //         while (destination_id == -1)
    //         {
    //             travel_dir = clockwise(travel_dir);
    //             destination_id = tiles[tileId].adjacent_id[travel_dir];
    //         }
    //     }
    // }

    int32_t newEncoderValue1 = encoder1.getCount();

    if (lastEncoderValue1 != newEncoderValue1)
    {
        // if (newEncoderValue1 > lastEncoderValue1)
        // {
        //     do
        //     {
        //         travel_dir = clockwise(travel_dir);
        //         destination_id = tiles[tileId].adjacent_id[travel_dir];
        //     }
        //     while (destination_id == -1);
        // }
        // else
        // {
        //     do
        //     {
        //         travel_dir = counter_clockwise(travel_dir);
        //         destination_id = tiles[tileId].adjacent_id[travel_dir];
        //     }
        //     while (destination_id == -1);
        // }

        term.attr(AnsiTerm::FG_Red);
        term.print("Encoder: ");
        term.println(newEncoderValue1);
        term.attr();
        lastEncoderValue1 = newEncoderValue1;
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

    static uint32_t previousCard1 = 0;

    card1.scan();

    if (card1.getUid() != previousCard1)
    {
        previousCard1 = card1.getUid();

        if (previousCard1 == 0)
        {
            term.attr(AnsiTerm::FG_Red);
            term.println("Card removed.");
            term.attr();

            game.signal(CardEvent(0, false));
        }
        else
        {
            term.attr(AnsiTerm::FG_Red, AnsiTerm::BOLD);
            term.print("Card scan: ");
            term.println(card1.getUid());
            term.attr();

            game.signal(CardEvent(0, true));
        }
    }
    static uint32_t previousCard2 = 0;

    card2.scan();

    if (card2.getUid() != previousCard2)
    {
        previousCard2 = card2.getUid();

        if (previousCard2 == 0)
        {
            term.attr(AnsiTerm::FG_Blue);
            term.println("Card removed.");
            term.attr();

            game.signal(CardEvent(1, false));
        }
        else
        {
            term.attr(AnsiTerm::FG_Blue, AnsiTerm::BOLD);
            term.print("Card scan: ");
            term.println(card2.getUid());
            term.attr();

            game.signal(CardEvent(1, true));
        }
    }
    static uint32_t previousCard3 = 0;

    card3.scan();

    if (card3.getUid() != previousCard3)
    {
        previousCard3 = card3.getUid();

        if (previousCard3 == 0)
        {
            term.attr(AnsiTerm::FG_Green);
            term.println("Card removed.");
            term.attr();

            game.signal(CardEvent(2, false));
        }
        else
        {
            term.attr(AnsiTerm::FG_Green, AnsiTerm::BOLD);
            term.print("Card scan: ");
            term.println(card3.getUid());
            term.attr();

            game.signal(CardEvent(2, true));
        }
    }

    static uint32_t previousCard4 = 0;

    card4.scan();

    if (card4.getUid() != previousCard4)
    {
        previousCard4 = card4.getUid();

        if (previousCard4 == 0)
        {
            term.attr(AnsiTerm::FG_Yellow);
            term.println("Card removed.");
            term.attr();

            game.signal(CardEvent(3, false));
        }
        else
        {
            term.attr(AnsiTerm::FG_Yellow, AnsiTerm::BOLD);
            term.print("Card scan: ");
            term.println(card4.getUid());
            term.attr();

            game.signal(CardEvent(3, true));
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
