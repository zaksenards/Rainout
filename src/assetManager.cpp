#include <rainout/assetManager.h>
#include <rainout/utils.h>
#include <cstdio>

namespace rainout
{
    Texture* AssetManager::loadTexture(const char* filePath)
    {
        char* binary = Utils::loadBinaryToBuffer(filePath);
        if(!binary)
            return nullptr;

        Texture* texture = new Texture;
        BitmapHeader* bitmap = (BitmapHeader*)binary;
        texture->width = bitmap->width;
        texture->height = bitmap->height;
        texture->data = binary+sizeof(BitmapHeader);
        texture->bitCount = bitmap->bitCount;

        return texture;
    }

    void AssetManager::destroyTexture(Texture* texture)
    {
        delete texture;
    }
}
