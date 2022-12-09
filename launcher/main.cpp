#define GLFW_INCLUDE_NONE
#include <rainout/assetManager.h>
#include <rainout/transform.h>
#include <rainout/material.h>
#include <rainout/matrix.h>
#include <rainout/entity.h>
#include <rainout/vector.h>
#include <rainout/scene.h>
#include <openglRender.h>
#include <glfw/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include <math.h>

using rainout::AssetManager;
using rainout::Material;
using rainout::Texture;
using rainout::Entity;
using rainout::Vec3f;
using rainout::Vec2f;
using rainout::Mat4f;
using rainout::Scene;

int main(void)
{
    if(!glfwInit())
    {
        fprintf(stderr, "Can't initialize API\n");
        return -1;
    }

    glfwWindowHint(GLFW_VISIBLE, false);
    glfwWindowHint(GLFW_DOUBLEBUFFER, true);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0x3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0x2);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "Rainout", 0, 0);
    if(!window)
    {
        fprintf(stderr, "Can't create window\n");
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!rainoutCore::init(glfwGetProcAddress))
    {
        fprintf(stderr, "Can't initialize Renderer\n");
        return -1;
    }

    Texture* texture = AssetManager::loadTexture("res/Player.bmp");
    Entity* player = Scene::createEntity(texture);


    texture = AssetManager::loadTexture("res/red.bmp");
    Entity* red = Scene::createEntity(texture);
    red->translate(Vec2f(-0.5f, 0.2f));

    glfwShowWindow(window);
    int frames = 0;
    double previus = glfwGetTime();
    double dt = 0;

    float angle = 10;
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        Vec2f translation;
        translation.x = (float) -((glfwGetKey(window, GLFW_KEY_A) - glfwGetKey(window, GLFW_KEY_D))*0.5*dt); 
        translation.y = (float) -((glfwGetKey(window, GLFW_KEY_S) - glfwGetKey(window, GLFW_KEY_W))*0.5*dt);

        player->translate(translation);

        double current = glfwGetTime();
        frames++;

        rainoutCore::update();
        if(current - previus <= (30.f/1.0f))
        {
            dt = current-previus;
            frames = 0;
            previus = current;

            if(glfwGetKey(window, GLFW_KEY_D))
                player->rotate(Vec2f(0.0f, 1.0f), 3.1415f);
            else if(glfwGetKey(window, GLFW_KEY_A))
                player->rotate(Vec2f(0.0f, 1.0f), 0.0f);

            angle+=0.1f;
            red->rotate(Vec2f(0.0f, 1.0f),angle);
            red->translate(Vec2f(sin(glfwGetTime())*0.5f*dt, 0.0f));
            Scene::render();
        }
        glfwSwapBuffers(window);
    }

    Scene::destroy();
    
    glfwTerminate();
    return 0;
}
