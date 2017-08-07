#include"OpenCLCommon.h"

cl_platform_id* GetPlatform(cl_uint* numPlatform)
{
	cl_int err;
	err = clGetPlatformIDs(0, NULL, numPlatform);
	CheckErr(err, __LINE__);

	cl_platform_id* platform = NULL;
	platform = (cl_platform_id*)malloc(*numPlatform * sizeof(cl_platform_id));
	
	err = clGetPlatformIDs(*numPlatform, platform, NULL);
	CheckErr(err, __LINE__);

	return platform;
}