#include "Arduino.h"

#include "CardInterface.h"

static uint8_t kKeya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
static int kReadTimeout = 20;

CardInterface::CardInterface(const CardInterface::Config& config)
    : _nfc(config.chipSelectPin)
    , _uidValid(false)
    , _uid(0)
{
}

void CardInterface::init()
{
    _nfc.begin();

    uint32_t versiondata = _nfc.getFirmwareVersion();
    if (! versiondata)
    {
        Serial.print("Didn't detect NFC board");
        //while (1); // halt
    }

    // configure board to read RFID tags
    _nfc.SAMConfig();
}

bool CardInterface::scan()
{
    _uidValid = false;
    _uid = 0;

    bool success;

    uint8_t uidLength;
    uint8_t uid[7] = {0};

    success = _nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, kReadTimeout);

    if (success)
    {
        if (uidLength != 4)
        {
            success = false;
        }
        else
        {
            _uid = reinterpret_cast<uint32_t*>(uid)[0];
            _uidValid = true;
        }
    }

    return success;
}

uint32_t CardInterface::getUid()
{
    return _uid;
}

bool CardInterface::readBlock(uint8_t block, uint8_t* data)
{
    if (!_uidValid)
    {
        return false;
    }

    bool success = _nfc.mifareclassic_AuthenticateBlock(reinterpret_cast<uint8_t*>(&_uid), 4, block, 0, kKeya);

    if (success)
    {
        success = _nfc.mifareclassic_ReadDataBlock(block, data);
    }

    return success;
}

bool CardInterface::writeBlock(uint8_t block, uint8_t* data)
{
    if (!_uidValid)
    {
        return false;
    }

    bool success = _nfc.mifareclassic_AuthenticateBlock(reinterpret_cast<uint8_t*>(&_uid), 4, block, 0, kKeya);

    if (success)
    {
        success = _nfc.mifareclassic_WriteDataBlock(block, data);
    }

    return success;
}

