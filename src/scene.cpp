#include <openglRender.h>
#include <rainout/scene.h>

using rainoutCore::glRender;

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
        glRender::Primitive model = glRender::createPrimitive();
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
        for(int i = 0; i < nodes.size(); i++)
            glRender::deletePrimitive(nodes.at(i)->getPrimitive());
    }
}
