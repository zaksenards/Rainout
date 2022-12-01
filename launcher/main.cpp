#define GLFW_INCLUDE_NONE
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

using rainout::Entity;
using rainout::Vec3f;
using rainout::Vec2f;
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

    Entity* player = Scene::createEntity();

    glfwShowWindow(window);
    int frames = 0;
    double previus = glfwGetTime();
    double dt = 0;
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
            Scene::render();
        }
        glfwSwapBuffers(window);
    }

    Scene::destroy();
    
    glfwTerminate();
    return 0;
}
