#ifndef rainout_keyboard_h
#define rainout_keyboard_h
#include <rainout/rainout.h>

#define VKCODE_UNKNOWN            -1
#define VKCODE_SPACE              32
#define VKCODE_APOSTROPHE         39  /* ' */
#define VKCODE_COMMA              44  /* , */
#define VKCODE_MINUS              45  /* - */
#define VKCODE_PERIOD             46  /* . */
#define VKCODE_SLASH              47  /* / */
#define VKCODE_0                  48
#define VKCODE_1                  49
#define VKCODE_2                  50
#define VKCODE_3                  51
#define VKCODE_4                  52
#define VKCODE_5                  53
#define VKCODE_6                  54
#define VKCODE_7                  55
#define VKCODE_8                  56
#define VKCODE_9                  57
#define VKCODE_SEMICOLON          59  /* ; */
#define VKCODE_EQUAL              61  /* = */
#define VKCODE_A                  65
#define VKCODE_B                  66
#define VKCODE_C                  67
#define VKCODE_D                  68
#define VKCODE_E                  69
#define VKCODE_F                  70
#define VKCODE_G                  71
#define VKCODE_H                  72
#define VKCODE_I                  73
#define VKCODE_J                  74
#define VKCODE_K                  75
#define VKCODE_L                  76
#define VKCODE_M                  77
#define VKCODE_N                  78
#define VKCODE_O                  79
#define VKCODE_P                  80
#define VKCODE_Q                  81
#define VKCODE_R                  82
#define VKCODE_S                  83
#define VKCODE_T                  84
#define VKCODE_U                  85
#define VKCODE_V                  86
#define VKCODE_W                  87
#define VKCODE_X                  88
#define VKCODE_Y                  89
#define VKCODE_Z                  90
#define VKCODE_LEFT_BRACKET       91  /* [ */
#define VKCODE_BACKSLASH          92  /* \ */
#define VKCODE_RIGHT_BRACKET      93  /* ] */
#define VKCODE_GRAVE_ACCENT       96  /* ` */
#define VKCODE_WORLD_1            161 /* non-US #1 */
#define VKCODE_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define VKCODE_ESCAPE             256
#define VKCODE_ENTER              257
#define VKCODE_TAB                258
#define VKCODE_BACKSPACE          259
#define VKCODE_INSERT             260
#define VKCODE_DELETE             261
#define VKCODE_RIGHT              262
#define VKCODE_LEFT               263
#define VKCODE_DOWN               264
#define VKCODE_UP                 265
#define VKCODE_PAGE_UP            266
#define VKCODE_PAGE_DOWN          267
#define VKCODE_HOME               268
#define VKCODE_END                269
#define VKCODE_CAPS_LOCK          280
#define VKCODE_SCROLL_LOCK        281
#define VKCODE_NUM_LOCK           282
#define VKCODE_PRINT_SCREEN       283
#define VKCODE_PAUSE              284
#define VKCODE_F1                 290
#define VKCODE_F2                 291
#define VKCODE_F3                 292
#define VKCODE_F4                 293
#define VKCODE_F5                 294
#define VKCODE_F6                 295
#define VKCODE_F7                 296
#define VKCODE_F8                 297
#define VKCODE_F9                 298
#define VKCODE_F10                299
#define VKCODE_F11                300
#define VKCODE_F12                301
#define VKCODE_F13                302
#define VKCODE_F14                303
#define VKCODE_F15                304
#define VKCODE_F16                305
#define VKCODE_F17                306
#define VKCODE_F18                307
#define VKCODE_F19                308
#define VKCODE_F20                309
#define VKCODE_F21                310
#define VKCODE_F22                311
#define VKCODE_F23                312
#define VKCODE_F24                313
#define VKCODE_F25                314
#define VKCODE_KP_0               320
#define VKCODE_KP_1               321
#define VKCODE_KP_2               322
#define VKCODE_KP_3               323
#define VKCODE_KP_4               324
#define VKCODE_KP_5               325
#define VKCODE_KP_6               326
#define VKCODE_KP_7               327
#define VKCODE_KP_8               328
#define VKCODE_KP_9               329
#define VKCODE_KP_DECIMAL         330
#define VKCODE_KP_DIVIDE          331
#define VKCODE_KP_MULTIPLY        332
#define VKCODE_KP_SUBTRACT        333
#define VKCODE_KP_ADD             334
#define VKCODE_KP_ENTER           335
#define VKCODE_KP_EQUAL           336
#define VKCODE_LEFT_SHIFT         340
#define VKCODE_LEFT_CONTROL       341
#define VKCODE_LEFT_ALT           342
#define VKCODE_LEFT_SUPER         343
#define VKCODE_RIGHT_SHIFT        344
#define VKCODE_RIGHT_CONTROL      345
#define VKCODE_RIGHT_ALT          346
#define VKCODE_RIGHT_SUPER        347
#define VKCODE_MENU               348
#define VKCODE_LAST               VKCODE_MENU

namespace rainout
{
    struct RAINOUT Keyboard
    {
        static bool isKeyDown(int vkCode);
        static bool isKeyPressed(int vkCode);
    };
}

#endif
