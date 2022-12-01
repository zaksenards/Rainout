#ifndef RAINOUT_TRANSFORM_H
#define RAINOUT_TRANSFORM_H
#include <rainout/vector.h>
#include <rainout/matrix.h>

namespace rainout
{
    struct Transform
    {
        float rotation;
        Vec2f position;
        Mat4f matrix;
        Vec2f scale;
    };
}

#endif//RAINOUT_TRANSFORM_H
