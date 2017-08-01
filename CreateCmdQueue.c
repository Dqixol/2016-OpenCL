#include "OpenCLCommon.h"

cl_command_queue CreateCmdQueue(cl_context context, cl_device_id device)
{
    cl_int errNum;
    cl_command_queue cmdQueue = NULL;
    cmdQueue = clCreateCommandQueue(context, device, 0, &errNum);
    if(cmdQueue == NULL || errNum != CL_SUCCESS)
    {
        printf("Failed to create cmdQueue on device 0\n");
        return NULL;
    }
    return cmdQueue;
}
