#include "OpenCLCommon.h"

cl_context CreateContext(cl_device_id* devices)
{
    cl_int errNum;
    cl_uint numPlatform;
    cl_platform_id firstPlatformID;
    cl_context context = NULL;
    errNum = clGetPlatformIDs(1, &firstPlatformID, &numPlatform);
    if(errNum != CL_SUCCESS || numPlatform < 1)
    {
        printf("Failed to find any OpenCL Devices\n");
        return NULL;
    }
    errNum = clGetDeviceIDs(firstPlatformID, CL_DEVICE_TYPE_GPU, 1, devices, NULL);
    if(errNum != CL_SUCCESS)
    {
        printf("There's no GPU, trying CPU...\n");
        errNum = clGetDeviceIDs(firstPlatformID, CL_DEVICE_TYPE_CPU, 1, devices, NULL);
        if(errNum != CL_SUCCESS)
        {
            printf("There's no GPU or CPU\n");
            return NULL;
        }
    }
    context = clCreateContext(NULL, 1, devices, NULL, NULL, &errNum);
    if(errNum != CL_SUCCESS)
    {
        printf("Error creating context\n");
        return NULL;
    }
    return context;
}
