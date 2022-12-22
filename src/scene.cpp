#include <openglRender.h>
#include <rainout/scene.h>

namespace rainout
{
    std::vector<Entity*> nodes;

    Entity* Scene::createEntity()
    {
        return createEntity(nullptr);
    }

    Entity* Scene::createEntity(Texture* texture)
    {
        Entity* entity = new Entity;
        rainoutCore::glRender::glRender::glRender::Primitive model = 
            rainoutCore::glRender::glRender::glRender::createPrimitive(rainoutCore::glRender::RECTANGLE_PRIMITIVE);
        Material material;
        Mat4f matrix = Mat4f::identity();

        Transform transform;
        transform.scale = Vec2f(0.06, 0.06);
        material.color = Vec3f(1.0f, 0.0f, 0.0f);

        transform.matrix = matrix;
        entity->setTransform(transform);
        entity->scale(Vec2f(0.05f, 0.05f));
        entity->setMaterial(material);
        entity->setPrimitive(model);
        entity->setTexture(texture);
        entity->setColidible(false);
        nodes.push_back(entity);

        return entity;
    }

    void Scene::render()
    {
        for(Entity* node : nodes)
        {
            rainoutCore::glRender::glRender::glRender::Primitive model = node->getPrimitive();
            Material material = node->getMaterial();
            Transform transform = node->getTransform();

            rainoutCore::glRender::glRender::glRender::render(model,material,transform.matrix);
        }
    }

    void Scene::destroy()
    {
        for(int i = 0; i < nodes.size(); i++)
            rainoutCore::glRender::glRender::glRender::deletePrimitive(nodes.at(i)->getPrimitive());
    }
}
