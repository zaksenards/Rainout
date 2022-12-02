#ifndef OPENGL_RENDER_H
#define OPENGL_RENDER_H
#include <cstdint>

#define RAINOUT_IMPLEMENTATION
#define RAINOUT_PLATFORM_WINDOWS
#include <rainout/assetManager.h>
#include <rainout/material.h>
#include <rainout/vector.h>
#include <rainout/matrix.h>

#ifdef RAINOUT_IMPLEMENTATION
    #ifdef RAINOUT_PLATFORM_WINDOWS
        #include <windows.h>
        #define RAINOUT_CORE __declspec(dllexport)
    #else
        #error "Not implemented"
    #endif
#else
    #ifdef RAINOUT_PLATFORM_WINDOWS
        #include <windows.h>
        #define RAINOUT_CORE __declspec(dllimport)
    #else
        #error "Not implemented"
    #endif
#endif

struct RAINOUT_CORE rainoutCore
{
    enum
    {
        VERTEX_SHADER_TYPE = 0,
        FRAGMENT_SHADER_TYPE = 1
    };

    enum
    {
        RECTANGLE_PRIMITIVE = 1
    };

    struct Primitive
    {
        uint32_t text;
        uint32_t vao;
        uint32_t vbo;
        uint32_t ebo;
        uint32_t id;
    };

    static bool init(void* proc);
    static void stop();

    static uint32_t compileShader(uint8_t shaderType, char* source);
    static uint32_t compileProgram(uint32_t vertex, uint32_t fragment);
    
    static Primitive createPrimitive(uint8_t type);
    static void deletePrimitive(Primitive primitive);
    static void setPrimitiveTexture(Primitive* primitive, rainout::Texture* texture);

    static void render(Primitive primitive, rainout::Material material, rainout::Mat4f matrix);
    static void render(Primitive primitive);

    static void drawColor(float R, float G, float B, float A);
    static void update();
};

#endif//OPENGL_RENDER_H
