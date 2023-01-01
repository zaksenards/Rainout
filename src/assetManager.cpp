#include <rainout/assetManager.h>
#include <rainout/utils.h>
#include <cstdio>

#define BITMAP_SIGNATURE 0x4D42

namespace rainout
{
    Texture* AssetManager::loadTexture(const char* filePath)
    {
        char* binary = Utils::loadBinaryToBuffer(filePath);
        if(!binary)
        {
            fprintf(stderr, "can't load file: %s",filePath);
            return new Texture();
        }

        BitmapHeader* bitmap = (BitmapHeader*)binary;
        if(bitmap->signature != BITMAP_SIGNATURE)
        {
            fprintf(stderr, "file: %s is not a bitmap\n",filePath);
            delete binary;
            return new Texture();
        }

        if(bitmap->compression != 3)
        {
            fprintf(stderr, "can't load bitamp %s with compressio\n",filePath);
            delete binary;
            return new Texture();
        }

        Texture* texture = new Texture((char*)bitmap+bitmap->dataOffset, bitmap->width, bitmap->height, bitmap->bitCount, false, 1, bitmap->width, bitmap->height);

        return texture;
    }

    Texture* AssetManager::loadAnimatedTexture(const char* filePath, uint8_t frames, uint8_t frameWidth, uint8_t frameHeight)
    {
        char* binary = Utils::loadBinaryToBuffer(filePath);
        if(!binary)
        {
            fprintf(stderr, "can't load file: %s",filePath);
            return new Texture();
        }

        BitmapHeader* bitmap = (BitmapHeader*)binary;
        if(bitmap->signature != BITMAP_SIGNATURE)
        {
            fprintf(stderr, "file: %s is not a bitmap\n",filePath);
            delete binary;
            return new Texture();
        }

        if(bitmap->compression != 3)
        {
            fprintf(stderr, "can't load bitamp %s with compressio\n",filePath);
            delete binary;
            return new Texture();
        }

        Texture* texture = new Texture((char*)bitmap+bitmap->dataOffset, bitmap->width, bitmap->height, bitmap->bitCount, true, frames, frameWidth, frameHeight);

        return texture;
    }

    void AssetManager::deleteTexture(Texture* texture)
    {
        delete texture->getData();
        delete texture;
    }
}
