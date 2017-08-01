#include "OpenCLCommon.h"
cl_program CreateProgramSource(cl_context context, cl_device_id device, const char* fileName)
{
    cl_int errNum;
    cl_program program;
    size_t programLength;
    const char* source = ReadKernelSourceFile(fileName, &programLength);
    program = clCreateProgramWithSource(context, 1, &source, NULL, &errNum);
    if(program == NULL || errNum != CL_SUCCESS)
    {
        printf("Failed to create CL program from %s", fileName);
        return NULL;
    }
    errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
    if(errNum != CL_SUCCESS)
    {
        char buildLog[16384];
        clGetProgramInfo(program, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), NULL, NULL);
        printf("Error in kernel :\n%s\n",buildLog);
        return NULL;
    }
    return program;
}
