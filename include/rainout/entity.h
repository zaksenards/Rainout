#ifndef entity_h
#define entity_h
#include <rainout/matrix.h>
#include <rainout/vector.h>
#include <rainout/material.h>
#include <rainout/transform.h>
#include <rainout/rainout.h>
#include <openglRender.h>

namespace rainout
{
    class RAINOUT Entity
    {
        public:
            void setTransform(Transform transform);
            Transform getTransform();

            void setMaterial(Material material);
            Material getMaterial();

            rainoutCore::Primitive getPrimitive();
            void setPrimitive(rainoutCore::Primitive obj);

            void setColor(Vec3f color);
            void translate(Vec2f translation);
            void scale(Vec2f scale);
        private:
            Material m_material;
            Transform m_transform;
            rainoutCore::Primitive m_primitive;
    };
}

#endif//entity_h
