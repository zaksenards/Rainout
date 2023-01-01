#include <rainout/keyboard.h>
#include <rainout/engine.h>
#include <windowManager.h>
#include <openglRender.h>
#include <cstdlib>
#include <cstdio>
#include <math.h>

using rainoutCore::WindowManager;
using rainoutCore::glRender;
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

    if(!WindowManager::init())
    {
        fprintf(stderr, "Can't initialize window\n");
        return -1;
    }

    GameSettings settings;

    onInit(&settings);
    if(!WindowManager::createWindow(settings.width, settings.height, settings.title))
    {
        fprintf(stderr, "Can't create window\n");
        return -1;
    }

    if(!glRender::init(WindowManager::getAddress()))
    {
        fprintf(stderr, "Can't initialize Renderer\n");
        return -1;
    }

    onStart();

    int frames = 0;
    float previus = (float)WindowManager::getTime(); 
    float dt = 0.0f;

    glRender::drawColor(settings.backColor);
    WindowManager::showWindow(true);
    while(!WindowManager::shouldClose())
    {
        WindowManager::update();

        float current = (float)WindowManager::getTime();
        frames++;

        glRender::update();
        if(current - previus <= (30.f/1.0f))
        {
            dt = (float) current-previus;
            frames = 0;
            previus = current;
            Scene::render();
        }
        onUpdate(dt);
        WindowManager::swapBuffers();
    }

    Scene::destroy();
    onStop();
    WindowManager::stop();
    return 0;
}
