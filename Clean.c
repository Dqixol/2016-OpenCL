#include"OpenCLCommon.h"
void Clean(cl_context context, cl_command_queue cmdQueue, cl_program program, cl_kernel kernel)
{
	if (context != NULL)
		clReleaseContext(context);
	if (cmdQueue != NULL)
		clReleaseCommandQueue(cmdQueue);
	if (program != NULL)
		clReleaseProgram(program);
	if (kernel != NULL)
		clReleaseKernel(kernel);
}