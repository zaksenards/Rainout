#ifndef rainout_window_h
#define rainout_window_h
#include <rainout/rainout.h>

namespace rainout
{
    struct RAINOUT Window
    {
        static bool init();
        static bool createWindow(const int width, const int height, const char* title);
        static void showWindow(bool value);
        static bool shouldClose();
        static void* getAddress();
        static double getTime();
        static int getKey(int key);
        static void stop();
        static void update();
        static void swapBuffers();
    };
};

#endif
