#ifndef RAINOUT_H
#define RAINOUT_H

//TODO: Fix dll export/inport
#ifndef RAINOUT_IMPLEMENTATION
    #define RAINOUT_IMPLEMENTATION
    #define RAINOUT_PLATFORM_WINDOWS
#endif

#ifdef RAINOUT_IMPLEMENTATION
    #ifdef RAINOUT_PLATFORM_WINDOWS
        #include <windows.h>
        #define RAINOUT __declspec(dllexport)
    #else
        #error "Not implemented"
    #endif
#else
    #ifdef RAINOUT_PLATFORM_WINDOWS
        #include <windows.h>
        #define RAINOUT __declspec(dllimport)
    #else
        #error "Not implemented"
    #endif
#endif

#endif//RAINOUT_H
