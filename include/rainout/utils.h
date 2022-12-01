#ifndef RAINOUT_UTILS_H
#define RAINOUT_UTILS_H
#include <cstdint>

#pragma pack(push, 1)
struct BitmapHeader
{
    uint16_t  fileType;      // File type; Must be BM
    uint32_t  fileSize;      // the size, in bytes, of the Bitmap file
    uint16_t  reserved1;     // Reserved; Must be zero
    uint16_t  rserved2;      // Reserved; Must be zero
    uint32_t  offset;        // The offset, in bytes, from the beginning of the BitmapHeader structure to the bitmap bits
    uint32_t  size;          // Specifies the size of the image, in bytes. This may be set to zero for BI_RGB bitmaps
    uint32_t  width;         // Specifies the width of the image
    uint32_t  height;        // Specifies the height of the image
    uint16_t  planes;        // Specifies the number of planes for the target device. This value must be set to 1
    uint16_t  bitCount;      // Specifies the number of bits per pixel
    uint32_t  compression;   // Specifies the type of compression for a compressed bottom-up bitmap
    uint32_t  sizeImage;     // Specifies the size of the image, in bytes. This may be set to zero for BI_RGB bitmaps
    uint32_t  xPelsPerMeter; // Specifies the horizontal resolution, in pixels per meter, of the target device for the bitmap
    uint32_t  yPelsPerMeter; // Specifies the vertical resolution, in pixels per meter, of the target device for the bitmap
    uint32_t  clrUsed;       // Specifies the number of color indexes in the color table that are actually used by the bitmap
    uint32_t  clrImportant;  // Specifies the number of color indexes required for displaying the bitmap.
    uint32_t colorRed;
    uint32_t colorGren;
    uint32_t colorBlue;
    uint32_t colorAlpha;
};
#pragma pack(pop)

struct Texture 
{
    uint32_t width;
    uint32_t height;
    char* data;
};

namespace Rainout
{
    struct Utils
    {
        static char* loadFileToBuffer(const char* filePath);
        static char* loadBinaryToBuffer(const char* filePath);
        static Texture* loadTexture(const char* filePath);
    };
}

#endif//RAINOUT_UTILS_H
