#define GLFW_INCLUDE_NONE
#include <windowManager.h>
#include <glfw/glfw3.h>

static GLFWwindow* window = nullptr;
bool WindowManager::init()
{
    if(!glfwInit())
        return 0;

    glfwWindowHint(GLFW_VISIBLE, false);
    glfwWindowHint(GLFW_DOUBLEBUFFER, true);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0x3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0x2);
    return 1;
}

bool WindowManager::createWindow(const int width, const int height, const char* title)
{
    window = glfwCreateWindow(width, height, title, 0, 0);
    if(!window)
        return 0;

    glfwMakeContextCurrent(window);

    return 1;
}

void* WindowManager::getAddress()
{
    return glfwGetProcAddress;
}

bool WindowManager::shouldClose()
{
    return glfwWindowShouldClose(window); 
}

double WindowManager::getTime()
{
    return glfwGetTime();
}

void WindowManager::stop()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}


void WindowManager::update()
{
    glfwPollEvents();
}

void WindowManager::swapBuffers()
{
    glfwSwapBuffers(window);
}

void WindowManager::showWindow(bool value)
{
    if(value)
        glfwShowWindow(window);
    else
        glfwHideWindow(window);
}

int WindowManager::getKeyState(int keyCode)
{
    return glfwGetKey(window, keyCode);
}
