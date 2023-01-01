#ifndef RAINOUT_MATERIAL_H
#define RAINOUT_MATERIAL_H
#include <rainout/assetManager.h>
#include <rainout/vector.h>

namespace rainout
{
    struct Material
    {
        Vec3f color;
        Texture* texture;
    };
}

#endif//RAINOUT_MATERIAL_H
