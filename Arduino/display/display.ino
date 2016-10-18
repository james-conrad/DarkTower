/*
 * This example shows how to display bitmaps that are exported from GIMP and
 * compiled into the sketch and stored in the Teensy's Flash memory
 * See more details here:
 * http://docs.pixelmatix.com/SmartMatrix/library.html#smartmatrix-library-how-to-use-the-library-drawing-raw-bitmaps
 *
 * This example uses only the SmartMatrix Background layer
 */

#include <SmartMatrix3.h>

#include "gimpbitmap.h"
#include "face.c"
#include "face2.c"
#include "tilemap.c"

#define COLOR_DEPTH 24                  // known working: 24, 48 - If the sketch uses type `rgb24` directly, COLOR_DEPTH must be 24
const uint8_t kMatrixWidth = 64;        // known working: 16, 32, 48, 64
const uint8_t kMatrixHeight = 32;       // known working: 32, 64, 96, 128
const uint8_t kRefreshDepth = 24;       // known working: 24, 36, 48
const uint8_t kDmaBufferRows = 4;       // known working: 2-4, use 2 to save memory, more to keep from dropping frames and automatically lowering refresh rate
const uint8_t kPanelType = SMARTMATRIX_HUB75_32ROW_MOD16SCAN;   // use SMARTMATRIX_HUB75_16ROW_MOD8SCAN for common 16x32 panels
const uint8_t kMatrixOptions = (SMARTMATRIX_OPTIONS_NONE);      // see http://docs.pixelmatix.com/SmartMatrix for options
const uint8_t kBackgroundLayerOptions = (SM_BACKGROUND_OPTIONS_NONE);
const uint8_t kScrollingLayerOptions = (SM_SCROLLING_OPTIONS_NONE);

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

SMARTMATRIX_ALLOCATE_BUFFERS(matrix, kMatrixWidth, kMatrixHeight, kRefreshDepth, kDmaBufferRows, kPanelType, kMatrixOptions);
SMARTMATRIX_ALLOCATE_BACKGROUND_LAYER(backgroundLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kBackgroundLayerOptions);
SMARTMATRIX_ALLOCATE_SCROLLING_LAYER(scrollingLayer, kMatrixWidth, kMatrixHeight, COLOR_DEPTH, kScrollingLayerOptions);

void drawBitmap(int16_t x, int16_t y, const gimpBitmap* bitmap) {
  for (unsigned int i=0; i < bitmap->height; i++) {
    for (unsigned int j=0; j < bitmap->width; j++) {
      rgb24 pixel = { bitmap->pixel_data[(i*bitmap->width + j)*3 + 0],
                      bitmap->pixel_data[(i*bitmap->width + j)*3 + 1],
                      bitmap->pixel_data[(i*bitmap->width + j)*3 + 2] };

      backgroundLayer.drawPixel(x + j, y + i, pixel);
    }
  }
}

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

void setup() {
  matrix.addLayer(&backgroundLayer);
  matrix.addLayer(&scrollingLayer); 
  matrix.begin();

  matrix.setBrightness(128);

  backgroundLayer.setRotation(rotation270);
  scrollingLayer.setOffsetFromTop(53);
  scrollingLayer.setRotation(rotation270);


}

int tileX = 0;
int tileY = 1;

void loop() {
  for (int i = 0; i <= 32; ++i) {
    backgroundLayer.fillScreen({0,0,0});
    drawBitmap(0,i,(const gimpBitmap*)&face);
    drawBitmap(0,32-i,(const gimpBitmap*)&face2);
    backgroundLayer.swapBuffers(true);
  }

  static bool monster = true;
  while (1) {
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

  darken(0, 28, 32, 34);
  backgroundLayer.swapBuffers(false);

  scrollingLayer.setColor({0xff, 0xff, 0xff});
  scrollingLayer.setMode(bounceForward);
  scrollingLayer.setSpeed(40);
  scrollingLayer.setFont(font3x5);
  scrollingLayer.start("FIGHT!", 1);

  while (scrollingLayer.getStatus());

  backgroundLayer.fillScreen({0,0,0});
  drawBitmap(0,0,(const gimpBitmap*)&face);
  drawBitmap(0,32,(const gimpBitmap*)&face2);
  backgroundLayer.swapBuffers();

  delay(2000);
}
