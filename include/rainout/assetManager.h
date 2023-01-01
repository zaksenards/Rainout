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
    class RAINOUT Texture 
    {
        public:
            Texture();
            ~Texture();
            Texture(char* data, uint32_t width, uint32_t height, uint32_t bitCount, bool animated, uint8_t frames, uint32_t frameW, uint32_t frameH);
            void setAnimationSpeed(float speed);
            uint8_t getAnimationIndex();
            uint8_t getAnimationGroup();
            uint32_t getFrameHeight();
            float getAnimationSpeed();
            uint8_t  getFrameCount();
            uint32_t getFrameWidth();
            uint32_t getBitCount();
            bool     isAnimated();
            uint32_t getHeight();
            void playAnimation();
            uint32_t getWidth();
            char* getData();
        private:
            float    _animationSpeed;
            uint32_t _frameHeight;
            uint32_t _frameWidth;
            uint32_t _bitCount;
            bool     _animated;
            uint32_t _height;
            uint8_t  _frames;
            uint32_t _width;
            float   _index;
            char*    _data;
    };

    struct RAINOUT AssetManager
    {
        static Texture* loadAnimatedTexture(const char* filePath, uint8_t frames, uint8_t frameWidth, uint8_t frameHeight);
        static Texture* loadTexture(const char* filePath);
        static void deleteTexture(Texture* texture);
    };
}

#endif//rainout_assetmanager_h
