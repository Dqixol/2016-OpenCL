#include "OpenCLCommon.h"
int main()
{
    cl_int errNum;
    cl_device_id devices = 0;
    
    sysinfo();
    
    cl_context          context     = CreateContext(&devices);
    
    cl_command_queue    cmdQueue    = CreateCmdQueue(context, devices);
    
    cl_program          program     = CreateProgramSource(context, devices, "/Users/dqicool/Documents/GitHub/OpenCl/vecadd.cl");
    
    cl_kernel           kernel      = clCreateKernel(program, "vecadd", &errNum);
    if(kernel == NULL)
    {
        printf("Failed Create kernel %d\n",errNum);
        return 1;
    }
}
