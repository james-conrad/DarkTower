#include "Arduino.h"

#include "TgaImage.h"

bool validateTga(const TgaImage::Header& header)
{
    /*
     * Color Map Type must be 1 (Color-mapped present)
     */
    if (header.colorMapType != 1)
    {
        return false;
    }

    /*
     * Image Type Code must be 1 (Color-mapped image) 
     */
    if (header.imageTypeCode != 1)
    {
        return false;
    }

    /*
     * Color map origin must be 0
     */
    if (header.colorMapOrigin != 0)
    {
        return false;
    }

    /*
     * Only 24-bit color maps are supported
     */
    if (header.colorMapDepth != 24)
    {
        return false;
    }

    /*
     * Only 8 bit index is supported for now.
     */
    if (header.bitsPerPixel != 8)
    {
        return false;
    }

    /*
     * Total number of colors in the color map must be less than
     * 256
     */
    if (header.colorMapCount > 256)
    {
        return false;
    }

    /*
     * Only an image origin of 0 is supported
     */
//    if (header.xOrigin != 0 || header.yOrigin != 0)
//    {
//        return false;
//    }

    return true;
}


void TgaImage::dumpHeader()
{
    Serial.print("Address: ");
    Serial.println(_file.getFlashAddress());

    if (!_isValid)
    {
        Serial.println("!!!! Invalid image !!!!");
    }

    Serial.print("Image Type code: ");
    Serial.println(_header.imageTypeCode);


    Serial.print("Color Map type: ");
    Serial.println(_header.colorMapType);

    Serial.print("Image dimensions: ");
    Serial.print(_header.imageWidth);
    Serial.print(",");
    Serial.println(_header.imageHeight);
    
    Serial.print("Image Depth: ");
    Serial.println(_header.bitsPerPixel);

    Serial.print("Color Map Depth: ");
    Serial.println(_header.colorMapDepth);

    Serial.print("Color Map Count: ");
    Serial.println(_header.colorMapCount);

    Serial.print("Color Map Origin: ");
    Serial.println(_header.colorMapOrigin);

    Serial.print("X Origin: ");
    Serial.println(_header.xOrigin);

    Serial.print("Y Origin: ");
    Serial.println(_header.yOrigin);
}

TgaImage::TgaImage()
    : _file()
    , _isValid(false)
    , _header()
{
}

bool TgaImage::isValid() const
{
    return _isValid;
}

bool TgaImage::load(const char* filename)
{
    _isValid = false;
    _file = SerialFlash.open(filename);
    if (_file)
    {
        if (_file.read(&_header, sizeof(_header)) == sizeof(_header))
        {
            _isValid = validateTga(_header);
        }
    }

    return _isValid;
}

bool TgaImage::makeResident(TgaImage::bgr24* colorMap, uint8_t* imageMap, uint32_t maxImageMapSize)
{
    if (!_isValid)
    {
        return false;
    }

    uint32_t imageMapSize = (_header.bitsPerPixel >> 3) * _header.imageWidth * _header.imageHeight;
    if (imageMapSize > maxImageMapSize)
    {
        return false;
    }

    uint32_t colorMapSize = (_header.colorMapDepth >> 3) * _header.colorMapCount;
    uint32_t colorMapOffset = sizeof(TgaImage::Header) + _header.idLength;
    
    _file.seek(colorMapOffset);
    if (_file.read(colorMap, colorMapSize) != colorMapSize)
    {
        return false;
    }

    if (_file.read(imageMap, imageMapSize) != imageMapSize)
    {
        return false;
    }


    return true;
}

