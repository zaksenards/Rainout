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

            void translate(Vec2f translation);
            void rotate(Vec2f rotation);
            void scale(Vec2f scale);
        private:
            Transform m_transform;
            Material m_material;
            rainoutCore::Primitive m_primitive;
    };
}

#endif//entity_h
