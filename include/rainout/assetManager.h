#ifndef rainout_assetmanager_h
#define rainout_assetmanager_h
#include <rainout/rainout.h>
#include <cstdint>

#pragma pack(push, 1)
struct BitmapHeader
{
    // Header 14 bytes
    uint16_t signature;
    uint32_t fileSize;
    uint32_t reserved1;
    uint32_t dataOffset;

    // Info header 40 bytes
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitCount;
    uint32_t compression;
    uint32_t sizeImage;
    uint32_t xPelsPerMeter;
    uint32_t yPelsPerMeter;
    uint32_t clrUsed;
    uint32_t clrImportant;

    // Color table 4 bytes
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t reserved3;
};
#pragma pack(pop)

namespace rainout
{
    struct Texture 
    {
        uint32_t width;
        uint32_t height;
        uint32_t bitCount;
        char* data;
    };

    struct RAINOUT AssetManager
    {
        static Texture* loadTexture(const char* filePath);
        static void destroyTexture(Texture* texture);
    };
}

#endif//rainout_assetmanager_h
