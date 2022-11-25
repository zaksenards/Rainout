#define GLFW_INCLUDE_NONE
#include <rainout/transform.h>
#include <rainout/material.h>
#include <rainout/matrix.h>
#include <openglRender.h>
#include <glfw/glfw3.h>
#include <cstdlib>
#include <cstdio>

using rainout::Material;
using rainout::Mat4f;
using rainout::Vec3f;

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

    rainoutCore::Primitive model = rainoutCore::createPrimitive(rainoutCore::RECTANGLE_PRIMITIVE);
    Material material;
    material.color = Vec3f(1.5f, 0.5f, 1.0f);

    Mat4f transform = Mat4f::identity();

    glfwShowWindow(window);
    rainoutCore::drawColor(0.5, 0.5, 1.0, 1.0);
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        rainoutCore::update();
        if(glfwGetKey(window, GLFW_KEY_D))
            transform = Mat4f::translate(transform, {0.01f, 0.0f, 0.0f});

        if(glfwGetKey(window, GLFW_KEY_A))
            transform = Mat4f::translate(transform, {-0.01f, 0.0f, 0.0f});

        if(glfwGetKey(window, GLFW_KEY_W))
            transform = Mat4f::translate(transform, {0.0f, 0.01f, 0.0f});

        if(glfwGetKey(window, GLFW_KEY_S))
            transform = Mat4f::translate(transform, {0.0f, -0.01f, 0.0f});

        rainoutCore::render(model, material, transform);

        glfwSwapBuffers(window);
    }
    
    rainoutCore::deletePrimitive(model);

    glfwTerminate();
    return 0;
}
