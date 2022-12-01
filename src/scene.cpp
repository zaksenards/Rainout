#include <openglRender.h>
#include <rainout/scene.h>

namespace rainout
{
    std::vector<Entity*> nodes;

    Entity* Scene::createEntity()
    {
        Entity* entity = new Entity;
        rainoutCore::Primitive model = 
            rainoutCore::createPrimitive(rainoutCore::RECTANGLE_PRIMITIVE);
        Material material;
        Mat4f matrix = Mat4f::identity();

        Transform transform;
        material.color = Vec3f(1.0f, 0.0f, 0.0f);

        transform.matrix = matrix;
        entity->setTransform(transform);
        entity->setMaterial(material);
        entity->setPrimitive(model);
        nodes.push_back(entity);

        return entity;
    }

    void Scene::render()
    {
        for(Entity* node : nodes)
        {
            rainoutCore::Primitive model = node->getPrimitive();
            Material material = node->getMaterial();
            Transform transform = node->getTransform();

            rainoutCore::render(model,material,transform.matrix);
        }
    }

    void Scene::destroy()
    {
        for(int i = 0; i < nodes.size(); i++)
            rainoutCore::deletePrimitive(nodes.at(i)->getPrimitive());
    }
}
