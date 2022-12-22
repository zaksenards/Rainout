#ifndef raintout_window_manager_h
#define raintout_window_manager_h

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

namespace rainoutCore
{
    struct RAINOUT_CORE WindowManager 
    {
        static bool init();
        static bool createWindow(const int width, const int height, const char* title);
        static void showWindow(bool value);
        static bool shouldClose();
        static void* getAddress();
        static double getTime();
        static int getKeyState(int key);
        static void stop();
        static void update();
        static void swapBuffers();
    };
}

#endif
