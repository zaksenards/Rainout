#include <rainout/engine.h>
#include <rainout/window.h>
#include <openglRender.h>
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
using rainout::Window;

int main(void)
{
    // Get game DLL function pointers
    HMODULE gameModule = LoadLibrary("rainout_game.dll");
    if(!gameModule)
    {
        fprintf(stderr, "Can't load game DLL\n");
        return -1;
    }

    ON_INIT_CALLBACK onInit = (ON_INIT_CALLBACK)GetProcAddress(gameModule, ON_INIT_FUNCTION_NAME);
    ON_STOP_CALLBACK onStop = (ON_STOP_CALLBACK)GetProcAddress(gameModule, ON_STOP_FUNCTION_NAME); 
    ON_START_CALLBACK onStart = (ON_START_CALLBACK)GetProcAddress(gameModule, ON_START_FUNCTION_NAME); 
    ON_UPDATE_CALLBACK onUpdate = (ON_UPDATE_CALLBACK)GetProcAddress(gameModule, ON_UPDATE_FUNCTION_NAME);

    if(!onStart || !onStop || !onUpdate || !onInit)
    {
        fprintf(stderr, "Can't load game functions\n");
        return -1;
    }

    if(!Window::init())
    {
        fprintf(stderr, "Can't initialize window\n");
        return -1;
    }

    int windowWith = 800, windowHeight = 600;
    onInit(&windowWith, &windowHeight);
    if(!Window::createWindow(windowWith, windowHeight, "Rainout"))
    {
        fprintf(stderr, "Can't create window\n");
        return -1;
    }

    if(!rainoutCore::init(Window::getAddress()))
    {
        fprintf(stderr, "Can't initialize Renderer\n");
        return -1;
    }

    onStart();

    int frames = 0;
    double previus = Window::getTime(); 
    float dt = 0;

    Window::showWindow(true);
    while(!Window::shouldClose())
    {
        Window::update();

        double current = Window::getTime();
        frames++;

        rainoutCore::update();
        if(current - previus <= (30.f/1.0f))
        {
            dt = (float) current-previus;
            frames = 0;
            previus = current;
            Scene::render();
        }
        onUpdate(dt);
        Window::swapBuffers();
    }

    Scene::destroy();
    onStop();
    Window::stop();
    return 0;
}
