#include <rainout/engine.h>
#include <glfw/glfw3.h>
#include <cstdio>

using rainout::AssetManager;
using rainout::Texture;
using rainout::Entity;
using rainout::Window;
using rainout::Scene;
using rainout::Vec2f;

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

void onInit(int* width, int* height)
{
    *width = 800;
    *height = 600;
}

void onStart()
{
    player = new Character("res/Player.bmp", Vec2f(0.0f, 0.0f));
    banner = new Character("res/red.bmp", Vec2f(-0.3f, -0.3f));
}

void onUpdate(float dt)
{
    Vec2f translation;
    translation.x = (float) -((Window::getKey(GLFW_KEY_A) - Window::getKey(GLFW_KEY_D))*0.5*dt); 
    translation.y = (float) -((Window::getKey(GLFW_KEY_S) - Window::getKey(GLFW_KEY_W))*0.5*dt);

    if(Window::getKey(GLFW_KEY_D))
        player->rotate(Vec2f(0.0f, 1.0f), 3.1415f);
    else if(Window::getKey(GLFW_KEY_A))
        player->rotate(Vec2f(0.0f, 1.0f), 0.0f);

    player->move(translation);
}

void onStop()
{
    delete player;
    delete banner;
}
