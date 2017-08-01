#include "OpenCLCommon.h"
char* ReadKernelSourceFile(const char* filename, size_t *length)
{
    FILE *file = NULL;
    size_t sourceLength;
    char* sourceString;
    size_t ret;
    file = fopen(filename, "rb");
    if(file == NULL)
    {
        printf("%s cannot be open\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    sourceLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    sourceString = (char*)malloc(sourceLength + 1);
    sourceString[0] = '\0';
    ret = fread(sourceString,sourceLength,1,file);
    if(ret == 0)
    {
        printf("%s cannot be read", filename);
        return NULL;
    }
    fclose(file);
    if(length != 0)
    {
        *length = sourceLength;
    }
    sourceString[sourceLength] = '\0';
    return sourceString;
}
