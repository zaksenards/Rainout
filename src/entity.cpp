#include <rainout/entity.h>

using rainout::Transform;
using rainout::Material;

namespace rainout
{
    void Entity::setTransform(Transform transform)
    {
        m_transform = transform;
    }

    Transform Entity::getTransform()
    {
        return m_transform;
    }

    void Entity::setMaterial(Material material)
    {
        m_material = material;
    }

    Material Entity::getMaterial()
    {
        return m_material;
    }

    rainoutCore::Primitive Entity::getPrimitive()
    {
        return m_primitive; 
    }

    void Entity::setTexture(Texture* texture)
    {
        if(!texture)
            return;

        m_texture = texture;
        rainoutCore::setPrimitiveTexture(&m_primitive, texture);
    }

    void Entity::setPrimitive(rainoutCore::Primitive primitive)
    {
        m_primitive = primitive;
    }

    void Entity::translate(Vec2f translation)
    {
        m_transform.position += translation;
        m_transform.matrix = 
            Mat4f::translate(m_transform.matrix, translation);
    }

    void Entity::scale(Vec2f scale)
    {
        m_transform.scale += scale;
        m_transform.matrix = Mat4f::scale(m_transform.matrix, scale);
    }

    void Entity::setColor(Vec3f color)
    {
        m_material.color = color;
    }
}
