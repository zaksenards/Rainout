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

    void scale(Vec2f scale)
    {
        entity->scale(scale);
    }

    bool isColliding(Character* right)
    {
        return entity->isColliding(right->entity);
    }
};

Vec2f ballDirection = Vec2f(-1, 0);
float ballSpeed = 0.5f;
Character* player1;
Character* player2;
Character* ball;

void onInit(GameSettings* settings)
{
    settings->title = (char*)"Pong";
    settings->height = 600;
    settings->width = 800;
    settings->backColor = Vec3f(0.2, 0.2, 0.4);
}

void onStart()
{
    player1 = new Character("res/paddle.bmp", Vec2f(-0.8f, 0.0f));
    player2 = new Character("res/paddle.bmp", Vec2f( 0.8f, 0.0f));

    ball = new Character("res/ball.bmp", Vec2f(-0.f, -0.f));
    player1->scale(Vec2f(0.04f, 0.4f));
    player2->scale(Vec2f(0.04f, 0.4f));

}

void onUpdate(float dt)
{
    Vec2f translation;
    translation.y = (float) -((Keyboard::isKeyDown(GLFW_KEY_S) - Keyboard::isKeyDown(GLFW_KEY_W))*0.5*dt);

    ball->move(ballDirection*ballSpeed*dt);
    if(ball->isColliding(player1) || ball->isColliding(player2))
        ballDirection = ballDirection.negative();

    player1->move(translation);
}

void onStop()
{
    delete player1;
    delete player2;
    delete ball;
}
