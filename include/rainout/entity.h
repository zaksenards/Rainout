#ifndef entity_h
#define entity_h
#include <rainout/matrix.h>
#include <rainout/vector.h>
#include <rainout/material.h>
#include <rainout/transform.h>
#include <rainout/rainout.h>

namespace rainout
{
    struct RAINOUT Entity
    {
        void setTransform(Transform transform);
        Transform getTransform();

        void setMaterial(Material material);
        Material getMaterial();

        const void* getPrimitive();
        void setPrimitive(const void* primitive);

        void translate(Vec2f translation);
        void rotate(Vec2f rotation);
        void scale(Vec2f scale);
    };
}

#endif//entity_h
