#include"OpenCLCommon.h"

cl_context CreateContext(cl_platform_id* platform, int platformIndex, cl_device_id* device, cl_uint numDevice)
{
	cl_int err;
	cl_context context = NULL;
	cl_context_properties properties[] = { CL_CONTEXT_PLATFORM, (cl_context_properties)platform[platformIndex],0 };
	context = clCreateContext(properties, numDevice, device, NULL, NULL, &err);
	CheckErr(err, __LINE__);
	return context;
}