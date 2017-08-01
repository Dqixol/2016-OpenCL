#include "OpenCLCommon.h"

void Cleanup(cl_context context, cl_command_queue cmdQueue, cl_program program, cl_kernel kernel)
{
    if (cmdQueue != 0)
    {
        clReleaseCommandQueue(cmdQueue);
    }
    if (context != 0)
    {
        clReleaseContext(context);
    }
    if (program != 0)
    {
        clReleaseProgram(program);
    }
    if (kernel != 0) {
        clReleaseKernel(kernel);
    }
}
