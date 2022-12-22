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

    rainoutCore::glRender::Primitive Entity::getPrimitive()
    {
        return m_primitive; 
    }

    void Entity::setTexture(Texture* texture)
    {
        if(!texture)
            return;

        m_texture = texture;
        rainoutCore::glRender::setPrimitiveTexture(&m_primitive, texture);
    }

    void Entity::setPrimitive(rainoutCore::glRender::Primitive primitive)
    {
        m_primitive = primitive;
    }

    void Entity::translate(Vec2f translation)
    {
        m_transform.position += translation;
        m_transform.matrix = Mat4f::translate(m_transform.matrix, translation);
    }

    void Entity::rotate(Vec2f rotation, float angle)
    {
        m_transform.rotation += Vec3f(rotation.x, rotation.y, 0.0f);
        m_transform.matrix = Mat4f::rotate(m_transform.matrix, Vec3f(rotation.x, rotation.y, 0.0f), angle);
    }

    void Entity::scale(Vec2f scale)
    {
        m_transform.scale = scale;
        m_transform.matrix = Mat4f::scale(m_transform.matrix, scale);
    }

    void Entity::setColor(Vec3f color)
    {
        m_material.color = color;
    }

    bool Entity::isColidible()
    {
        return m_colider.colidible;
    }
    
    void Entity::setColidible(bool state)
    {
        m_colider.colidible = state;
    }
    bool Entity::isColliding(Entity* other)
    {
        if(other == nullptr)
            return false;
        Transform otherTransform = other->getTransform();
        Vec2f otherPosition = otherTransform.position;
        Vec2f otherScale = otherTransform.scale;
        Vec2f myPosition = m_transform.position;
        Vec2f myScale = m_transform.scale;

        bool left = myPosition.x+(myScale.x) >= otherPosition.x-(otherScale.x);
        bool right = myPosition.x-(myScale.x) <= otherPosition.x+(otherScale.x);

        bool top = myPosition.y-(myScale.y) <= otherPosition.y+(otherScale.y);
        bool down = myPosition.y+(myScale.y) >= otherPosition.y-(otherScale.y);

        return (left && right) && (top && down);
    }
}
