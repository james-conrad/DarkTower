#ifndef _TGA_IMAGE_H_
#define _TGA_IMAGE_H_

#include <SmartMatrix3.h>
#include <SerialFlash.h>

class TgaImage
{
public:
    struct Header
    {
        uint8_t idLength;
        uint8_t colorMapType;
        uint8_t imageTypeCode;
        uint16_t colorMapOrigin;
        uint16_t colorMapCount;
        uint8_t colorMapDepth;
        uint16_t xOrigin;
        uint16_t yOrigin;
        uint16_t imageWidth;
        uint16_t imageHeight;
        uint8_t bitsPerPixel;
        uint8_t imageDescriptor;
    } __attribute__ ((packed));

    struct bgr24
    {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
    };

    TgaImage();

    bool load(const char* filename);
    bool isValid() const;
    bool makeResident(bgr24* colorMap, uint8_t* imageMap, uint32_t maxImageMapSize);

    const Header& getHeader() { return _header; }

    void dumpHeader();

private:
    SerialFlashFile _file;
    bool _isValid;
    Header _header;
};

#endif // _TGA_IMAGE_H_

