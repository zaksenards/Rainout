#include <rainout/engine.h>
#include <glfw/glfw3.h>
#include <cstdio>

using rainout::AssetManager;
using rainout::Keyboard;
using rainout::Texture;
using rainout::Entity;
using rainout::Scene;
using rainout::Vec2f;
using rainout::Vec3f;

struct Character
{
    Entity* entity;
    Texture* texture;

    Character(const char* text, Vec2f translation)
    {
        texture = AssetManager::loadTexture(text);
        entity = Scene::createEntity(texture);
        entity->translate(translation);
    }

    void move(Vec2f translation)
    {
        entity->translate(translation);
    }

    void rotate(Vec2f rotation, float angle)
    {
        entity->rotate(rotation, angle);
    }
};
Character* player;
Character* banner;

void onInit(GameSettings* settings)
{
    settings->title = (char*)"Character controller";
    settings->height = 600;
    settings->width = 800;
    settings->backColor = Vec3f(0.2, 0.2, 0.4);
}

void onStart()
{
    player = new Character("res/Player.bmp", Vec2f(0.0f, 0.0f));
    banner = new Character("res/red.bmp", Vec2f(-0.3f, -0.3f));
}

void onUpdate(float dt)
{
    Vec2f translation;
    translation.x = (float) -((Keyboard::isKeyDown(GLFW_KEY_A) - Keyboard::isKeyDown(GLFW_KEY_D))*0.5*dt); 
    translation.y = (float) -((Keyboard::isKeyDown(GLFW_KEY_S) - Keyboard::isKeyDown(GLFW_KEY_W))*0.5*dt);

    if(Keyboard::isKeyDown(GLFW_KEY_D))
        player->rotate(Vec2f(0.0f, 1.0f), 3.1415f);
    else if(Keyboard::isKeyDown(GLFW_KEY_A))
        player->rotate(Vec2f(0.0f, 1.0f), 0.0f);

    player->move(translation);
}

void onStop()
{
    delete player;
    delete banner;
}
