#include"OpenCLCommon.h"

void CheckErr(cl_int err, int num)
{
	if (err != CL_SUCCESS)
	{
		printf("OpenCL error(%d) at %d\n", err, num - 1);
		
	}
}