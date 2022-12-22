#ifndef entity_h
#define entity_h
#include <rainout/assetManager.h>
#include <rainout/matrix.h>
#include <rainout/vector.h>
#include <rainout/material.h>
#include <rainout/transform.h>
#include <rainout/rainout.h>
#include <rainout/collider.h>
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

            rainoutCore::glRender::Primitive getPrimitive();
            void setPrimitive(rainoutCore::glRender::Primitive obj);

            void setTexture(Texture* texture);

            void setColor(Vec3f color);
            void translate(Vec2f translation);
            void scale(Vec2f scale);
            void rotate(Vec2f rotation, float angle);

            bool isColidible();
            void setColidible(bool state);
            bool isColliding(Entity* other);
        private:
            Collider m_colider;
            Texture* m_texture;
            Material m_material;
            Transform m_transform;
            rainoutCore::glRender::Primitive m_primitive;
    };
}

#endif//entity_h
