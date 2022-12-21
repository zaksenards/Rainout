#define GLFW_INCLUDE_NONE
#include <rainout/window.h>
#include <glfw/glfw3.h>

namespace rainout
{
    static GLFWwindow* window = nullptr;
    bool Window::init()
    {
        if(!glfwInit())
            return 0;

        glfwWindowHint(GLFW_VISIBLE, false);
        glfwWindowHint(GLFW_DOUBLEBUFFER, true);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0x3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0x2);
        return 1;
    }

    bool Window::createWindow(const int width, const int height, const char* title)
    {
        window = glfwCreateWindow(width, height, title, 0, 0);
        if(!window)
            return 0;

        glfwMakeContextCurrent(window);

        return 1;
    }

    void* Window::getAddress()
    {
        return glfwGetProcAddress;
    }

    bool Window::shouldClose()
    {
        return glfwWindowShouldClose(window); 
    }

    double Window::getTime()
    {
        return glfwGetTime();
    }

    void Window::stop()
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }


    void Window::update()
    {
        glfwPollEvents();
    }
    
    void Window::swapBuffers()
    {
        glfwSwapBuffers(window);
    }

    void Window::showWindow(bool value)
    {
        if(value)
            glfwShowWindow(window);
        else
            glfwHideWindow(window);
    }

    int Window::getKey(int keyCode)
    {
        return glfwGetKey(window, keyCode);
    }
}
