#include <openglRender.h>
#include <rainout/scene.h>

using rainoutCore::glRender;

namespace rainout
{
    std::vector<Entity*> nodes;

    Entity* Scene::createEntity()
    {
        Entity* entity = new Entity;
        glRender::Primitive model = glRender::createPrimitive();
        Material material;
        Mat4f matrix = Mat4f::identity();

        Transform transform;
        transform.scale = Vec2f(0.06f, 0.06f);
        material.color = Vec3f(1.0f, 0.0f, 0.0f);
        material.texture = nullptr;

        transform.matrix = matrix;
        entity->setTransform(transform);
        entity->scale(Vec2f(0.05f, 0.05f));
        entity->setMaterial(material);
        entity->setPrimitive(model);
        entity->setColidible(false);

        nodes.push_back(entity);

        return entity;
    }

    Entity* Scene::createEntity(Texture* texture)
    {
        Entity* entity = createEntity();
        entity->setTexture(texture);

        return entity;
    }

    void Scene::removeEntity(Entity* entity)
    {
        size_t index = 0;
        for(index; index < nodes.size();index++)
        {
            if(entity == nodes.at(index)){
                nodes.erase(nodes.begin()+index);
                break;
            }
        }
    }

    void Scene::render()
    {
        for(Entity* node : nodes)
        {
            glRender::Primitive model = node->getPrimitive();
            Material material = node->getMaterial();
            Transform transform = node->getTransform();

            Mat4f matrix = transform.matrix; 
            matrix = Mat4f::rotate(matrix, Vec3f(1.0f, 0.0f, 0.0f), transform.rotation.x);
            matrix = Mat4f::rotate(matrix, Vec3f(0.0f, 1.0f, 0.0f), transform.rotation.y);
            matrix = Mat4f::scale(matrix, transform.scale);
            matrix = Mat4f::translate(matrix, transform.position);

            glRender::render(model,material,matrix);
        }
    }

    void Scene::destroy()
    {
        for(size_t index = 0; index < nodes.size(); index++)
        {
            Entity* entity = nodes.at(index);
            glRender::deletePrimitive(entity->getPrimitive());
        }
    }
}
