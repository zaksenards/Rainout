#include <rainout/entity.h>
#include <openglRender.h>

using rainout::Transform;
using rainout::Material;

namespace rainout
{
    struct
    {
        rainoutCore::Primitive primitive;
        Transform transform;
        Material material;
    }_shared;

    void Entity::setTransform(Transform transform)
    {
        _shared.transform = transform;
    }

    Transform Entity::getTransform()
    {
        return _shared.transform;
    }

    void Entity::setMaterial(Material material)
    {
        _shared.material = material;
    }

    Material Entity::getMaterial()
    {
        return _shared.material;
    }

    const void* Entity::getPrimitive()
    {
        return &_shared.primitive; 
    }


    void Entity::setPrimitive(const void* primitive)
    {
        _shared.primitive = *(rainoutCore::Primitive*)primitive;
    }

    void Entity::translate(Vec2f translation)
    {
        _shared.transform.position += translation;
        _shared.transform.matrix = 
            Mat4f::translate(_shared.transform.matrix, translation);
    }

    void Entity::rotate(Vec2f rotation)
    {
        //TODO
        rotation = Vec2f(0.0f, 0.0f);
    }
    
    void Entity::scale(Vec2f scale)
    {
        //TODO
        scale = Vec2f(0.0f, 0.0f);
    }
}
