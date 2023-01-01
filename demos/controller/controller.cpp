#include <rainout/engine.h>
#include <glfw/glfw3.h>
#include <cstdio>
#include <cmath>

using rainout::AssetManager;
using rainout::Keyboard;
using rainout::Texture;
using rainout::Entity;
using rainout::Scene;
using rainout::Vec2f;
using rainout::Vec3f;

#define sign(x) (x <= 0? 0 : 1)

struct Character
{
    Entity* entity;
    Texture* walkTexture;
    Texture* idleTexture;
    Texture* current;
    bool isWalking, wasWalking;

    Character(const char* walkText, const char* idleText, Vec2f translation, uint8_t frames, uint8_t width, uint8_t height)
    {
        walkTexture = AssetManager::loadAnimatedTexture(walkText, frames, width, height);
        idleTexture = AssetManager::loadAnimatedTexture(idleText, frames, width, height);
        entity = Scene::createEntity(idleTexture);
        entity->translate(translation);
        isWalking = wasWalking = false;
        current = idleTexture;
    }

    void walk(Vec2f translation)
    {
        wasWalking = isWalking;

        if(!isWalking && translation.x != 0.00f){
            entity->setTexture(walkTexture);
            current = walkTexture;
        }

        entity->translate(translation);
        isWalking = true;
    }

    void idle()
    {
        isWalking = false;
        if(wasWalking)
            entity->setTexture(idleTexture);
        wasWalking = false;
        current = idleTexture;
    }

    void rotate(Vec2f rotation, float angle)
    {
        entity->rotate(rotation, angle);
    }

    void scale(float scale)
    {
        entity->scale(Vec2f(scale, scale));
    }

    void animationSpeed(float speed)
    {
        walkTexture->setAnimationSpeed(speed);
        idleTexture->setAnimationSpeed(speed);
    }

    void animate()
    {
        current->playAnimation();
    }
};
Character* player;

void onInit(GameSettings* settings)
{
    settings->title = (char*)"Character controller";
    settings->height = 600;
    settings->width = 800;
    settings->backColor = Vec3f(0.2f, 0.2f, 0.4f);
}

void onStart()
{
    player = new Character("assets/ghost-move.bmp", "assets/ghost-idle.bmp", Vec2f(0.4f, 0.4f), 8, 48, 48);
    player->animationSpeed(0.10f);
    player->scale(0.09f);
}

void onUpdate(float dt)
{
    Vec2f translation;
    float rotation;

    translation.x = (float) -((Keyboard::isKeyDown(GLFW_KEY_A) - Keyboard::isKeyDown(GLFW_KEY_D))*0.5*dt); 
    translation.y = (float) -((Keyboard::isKeyDown(GLFW_KEY_S) - Keyboard::isKeyDown(GLFW_KEY_W))*0.5*dt);
    rotation = sign((Keyboard::isKeyDown(VKCODE_A) - Keyboard::isKeyDown(VKCODE_D)))*3.1415f;
    player->rotate(Vec2f(0.0f, 1.0f), rotation);

    if(translation.magnitude() > 0)
        player->walk(translation);
    else
        player->idle();

    player->animationSpeed(0.10f);
    player->animate();
}

void onStop()
{
    delete player;
}
