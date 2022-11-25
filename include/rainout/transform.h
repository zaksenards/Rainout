#ifndef RAINOUT_TRANSFORM_H
#define RAINOUT_TRANSFORM_H
#include <rainout/Vector.h>

namespace rainout
{
    struct Transform
    {
        Vec2f rotation;
        Vec2f position;
        Vec2f scale;
    };
}

#endif//RAINOUT_TRANSFORM_H
