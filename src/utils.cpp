#define _CRT_SECURE_NO_WARNINGS
#include <rainout/utils.h>
#include <cstdlib>
#include <cstdio>

namespace Rainout
{
    char* Utils::loadFileToBuffer(const char* filePath)
    {
        FILE* fp = fopen(filePath, "r");
        if(!fp)
        {
           //TODO: Log error in debug mode 
           return nullptr;
        }

        fseek(fp, 0, SEEK_END);
        size_t fileSize = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        char* buffer = new char[fileSize];
        size_t bytes = fread(buffer, sizeof(char), fileSize, fp);
        fclose(fp);

        if(!bytes)
        {
           //TODO: Log error in debug mode 
           delete buffer;
           return nullptr;
        }

        buffer[bytes-1] = '\0';
        return buffer;
    }
}
