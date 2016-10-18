#include "Arduino.h"

#include "Display.h"
#include <SmartMatrix3.h>
#include "TgaImage.h"

#include "gimpbitmap.h"
#include "tilemap.c"

#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
const uint8_t kMatrixWidth = 64;        // known working: 16, 32, 48, 64
const uint8_t kMatrixHeight = 32;       // known working: 32, 64, 96, 128
const uint8_t kRefreshDepth = 24;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kIndexedLayerOptions = (SM_INDEXED_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
//SMARTMATRIX_ALLOCATE_INDEXED_LAYER(indexedLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kIndexedLayerOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);

TgaImage::bgr24 _tempColorMap[256];
uint8_t _tempImageMap[32*64]; 

template<typename T, size_t N>
size_t dim(const T (& array)[N])
{
   return N;
}

const char* descriptions[] = {
  "Dungeon Level 1",
  "The King will be pleased!",
  "DEATH LIES AHEAD!",
  "FIGHT!",
  "The battle has begun",
  "A reward for your long journey"
};


void drawTile(int16_t x, int16_t y, int tileX, int tileY, const gimpBitmap* bitmap) {
  const unsigned char* tile = &bitmap->pixel_data[(tileY * 32 * bitmap->width + tileX * 32) * 3];
  for (unsigned int i=0; i < 32; i++) {
    for (unsigned int j=0; j < 32; j++) {
      rgb24 pixel = rgb24(tile[0], tile[1], tile[2]);
      if (pixel.green != 0xff || pixel.red != 0 || pixel.blue != 0) {
        backgroundLayer.drawPixel(x + j, y + i, pixel);
      }
      tile += 3;
    }
    tile += (bitmap->width - 32) * 3;
  }
}

void darken(int x0, int y0, int x1, int y1)
{
  for (int y = y0; y <= y1; ++y)
  {
    for (int x = x0; x <= x1; ++x)
    {
      rgb24 pixel = backgroundLayer.readPixel(x,y);
      backgroundLayer.drawPixel(x, y, rgb24(pixel.red >> 1, pixel.green >> 1, pixel.blue >> 1));
    }
  }
}

Display::Display()
{}

void Display::init()
{
    matrix.addLayer(&backgroundLayer);
    //matrix.addLayer(&indexedLayer); 
    matrix.addLayer(&scrollingLayer); 
    matrix.begin();
    
    matrix.setBrightness(128);
    
    backgroundLayer.setRotation(rotation270);
    //indexedLayer.setRotation(rotation270);
    scrollingLayer.setOffsetFromTop(53);
    scrollingLayer.setRotation(rotation270);
}

void Display::update()
{
    static bool monster = true;

    int terrain = random(0, 8);
    drawTile(0, 0, terrain, 2, (const gimpBitmap*)&tilemap);
    drawTile(0, 32, terrain, 2, (const gimpBitmap*)&tilemap);
    
    if (monster)
    {
        int monsterX = random(0, 8);
        int monsterY = random(0, 2);
        drawTile(0, 16, monsterX, monsterY, (const gimpBitmap*)&tilemap);
    }
    else
    {
        int itemX = random(0, 8);
        int itemY = random(3, 8);
        drawTile(0, 16, itemX, itemY, (const gimpBitmap*)&tilemap);
    }
    
    monster = !monster;
    darken(0, 52, 32, 63);
    backgroundLayer.swapBuffers();
    
    scrollingLayer.setColor({0xff, 0xff, 0xff});
    scrollingLayer.setMode(bounceForward);
    scrollingLayer.setSpeed(40);
    scrollingLayer.setFont(font6x10);
    const char* text = descriptions[random(0, dim(descriptions))];
    scrollingLayer.start(text, 1);
    
    while (scrollingLayer.getStatus());
}

bool Display::setColorMap(TgaImage& image)
{
    if (!image.isValid())
    {
        return false;
    }

    const TgaImage::Header& header = image.getHeader();

    if (!image.makeResident(_tempColorMap, _tempImageMap, 2048))
    {
        return false;
    }

    for (int i = 0; i < header.colorMapCount; ++i)
    {
        TgaImage::bgr24& color = _tempColorMap[i];
        //indexedLayer.setIndexedColor(i, rgb24(color.red, color.green, color.blue));
        Serial.print(i);
        Serial.print(": ");
        Serial.print(color.red);        Serial.print(", ");
        Serial.print(color.green);      Serial.print(", ");
        Serial.print(color.blue);       Serial.println();
    }

    return true;
}

bool Display::drawIndexedImage(TgaImage& image)
{
    if (!image.isValid())
    {
        return false;
    }

    if (!image.makeResident(_tempColorMap, _tempImageMap, 2048))
    {
        return false;
    }

    const TgaImage::Header& header = image.getHeader();

    for (int y = 0; y < header.imageHeight; ++y)
    {
        for (int x = 0; x < header.imageWidth; ++x)
        {
            uint8_t index = _tempImageMap[y * header.imageWidth + x];
            //indexedLayer.drawPixel(x, y, index);  
        }
    }
    //indexedLayer.swapBuffers(true);

    return true;
}


bool Display::drawFullscreenImage(TgaImage& image)
{
    if (!image.isValid())
    {
        return false;
    }

    if (!image.makeResident(_tempColorMap, _tempImageMap, 2048))
    {
        return false;
    }

    const TgaImage::Header& header = image.getHeader();

    for (int y = 0; y < header.imageHeight; ++y)
    {
        for (int x = 0; x < header.imageWidth; ++x)
        {
            uint8_t index = _tempImageMap[y * header.imageWidth + x];
            TgaImage::bgr24& color = _tempColorMap[index];
            if (color.red != 0xff || color.blue != 0xff || color.green != 0x00)
            {
                backgroundLayer.drawPixel(x, y, rgb24(color.red, color.green, color.blue));
            }
        }
    }
    return true;
}

void Display::swapBuffers()
{
    backgroundLayer.swapBuffers();
}

