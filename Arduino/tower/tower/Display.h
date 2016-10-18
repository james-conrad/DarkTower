#ifndef _DISPLAY_H_
#define _DISPLAY_H_

class TgaImage;

class Display
{
public:
    Display();

    void init();
    void update();

    bool drawFullscreenImage(TgaImage& image);
    void swapBuffers(); 

    bool setColorMap(TgaImage& image);
    bool drawIndexedImage(TgaImage& image);
};

#endif // _DISPLAY_H_
