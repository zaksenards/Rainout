#ifndef rainout_assetmanager_h
#define rainout_assetmanager_h
#include <rainout/rainout.h>
#include <cstdint>

#pragma pack(push, 1)
struct BitmapHeader
{
    uint16_t fileType;      // File type; Must be BM
    uint32_t fileSize;      // the size, in bytes, of the Bitmap file
    uint16_t reserved1;     // Reserved; Must be zero
    uint16_t rserved2;      // Reserved; Must be zero
    uint32_t offset;        // The offset, in bytes, from the beginning of the BitmapHeader structure to the bitmap bits
    uint32_t size;          // Specifies the size of the image, in bytes. This may be set to zero for BI_RGB bitmaps
    uint32_t width;         // Specifies the width of the image
    uint32_t height;        // Specifies the height of the image
    uint16_t planes;        // Specifies the number of planes for the target device. This value must be set to 1
    uint16_t bitCount;      // Specifies the number of bits per pixel
    uint32_t compression;   // Specifies the type of compression for a compressed bottom-up bitmap
    uint32_t sizeImage;     // Specifies the size of the image, in bytes. This may be set to zero for BI_RGB bitmaps
    uint32_t xPelsPerMeter; // Specifies the horizontal resolution, in pixels per meter, of the target device for the bitmap
    uint32_t yPelsPerMeter; // Specifies the vertical resolution, in pixels per meter, of the target device for the bitmap
    uint32_t clrUsed;       // Specifies the number of color indexes in the color table that are actually used by the bitmap
    uint32_t clrImportant;  // Specifies the number of color indexes required for displaying the bitmap.
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
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
