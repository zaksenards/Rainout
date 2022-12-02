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
            return nullptr;
        BitmapHeader* bitmap = (BitmapHeader*)binary;
        if(bitmap->signature != BITMAP_SIGNATURE)
        {
            fprintf(stderr, "File: %s is not a bitmap\n",filePath);
            delete binary;
            return nullptr;
        }

        if(bitmap->compression != 3)
        {
            fprintf(stderr, "Can't load bitamp %s with compressio\n",filePath);
            delete binary;
            return nullptr;
        }

        Texture* texture = new Texture;
        texture->width = bitmap->width;
        texture->height = bitmap->height;
        texture->bitCount = bitmap->bitCount;
        texture->data = binary+bitmap->dataOffset;

        return texture;
    }

    void AssetManager::destroyTexture(Texture* texture)
    {
        delete texture;
    }
}
