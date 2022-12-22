#include <rainout/keyboard.h>
#include <windowManager.h>

#define KEY_DOWN 1
#define KEY_PRESS 2

namespace rainout
{
    bool Keyboard::isKeyDown(int vkCode)
    {
        return WindowManager::getKeyState(vkCode) == KEY_DOWN;
    }
    
    bool Keyboard::isKeyPressed(int vkCode)
    {
        return WindowManager::getKeyState(vkCode) == KEY_PRESS;
    }
}
