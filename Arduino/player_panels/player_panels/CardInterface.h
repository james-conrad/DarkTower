#ifndef _CARD_INTERFACE_H_
#define _CARD_INTERFACE_H_

#include <Adafruit_PN532.h>
#include <SPI.h>

class CardInterface
{
public:
    struct Config
    {
        int chipSelectPin;
    };

    CardInterface(const Config& config);

    void init();

    bool scan();
    uint32_t getUid();
    bool readBlock(uint8_t block, uint8_t* data);
    bool writeBlock(uint8_t block, uint8_t* data);

private:
    Adafruit_PN532 _nfc;

    bool _uidValid;
    uint32_t _uid;
};

#endif // _CARD_INTERFACE_H_
