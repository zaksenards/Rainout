#ifndef RAINOUT_ENGINE
#define RAINOUT_ENGINE

#include <rainout/assetManager.h>
#include <rainout/transform.h>
#include <rainout/material.h>
#include <rainout/matrix.h>
#include <rainout/entity.h>
#include <rainout/vector.h>
#include <rainout/window.h>
#include <rainout/scene.h>

const char* ON_INIT_FUNCTION_NAME = "onInit";
const char* ON_STOP_FUNCTION_NAME = "onStop";
const char* ON_START_FUNCTION_NAME = "onStart";
const char* ON_UPDATE_FUNCTION_NAME = "onUpdate";

typedef void (*ON_INIT_CALLBACK)(int* width, int* height);
typedef void (*ON_STOP_CALLBACK)();
typedef void (*ON_START_CALLBACK)();
typedef void (*ON_UPDATE_CALLBACK)(float dt);

#define RAINOUT_GAME __declspec(dllexport)

extern "C"
{
    RAINOUT_GAME void onInit(int* width, int* height);
    RAINOUT_GAME void onStop();
    RAINOUT_GAME void onStart();
    RAINOUT_GAME void onUpdate(float dt);
}
#endif
