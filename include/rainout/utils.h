#ifndef RAINOUT_UTILS_H
#define RAINOUT_UTILS_H

namespace rainout
{
    struct Utils
    {
        static char* loadFileToBuffer(const char* filePath);
        static char* loadBinaryToBuffer(const char* filePath);
    };
}

#endif//RAINOUT_UTILS_H
