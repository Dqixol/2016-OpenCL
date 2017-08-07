#include"OpenCLCommon.h"
void PrintPlatformInfo(cl_platform_id* platform, cl_uint numPlatform)
{
	cl_int err;
	char str[512];
	size_t size = sizeof(str);
	for (int i = 0; i < numPlatform; i++)
	{
		printf("\nPlatform [%d]: \n", i);
		err = clGetPlatformInfo(platform[i], CL_PLATFORM_NAME, size, str, NULL);
		printf("Name		%s \n", str);
		err = clGetPlatformInfo(platform[i], CL_PLATFORM_VERSION, size, str, NULL);
		printf("Version		%s \n", str);
		err = clGetPlatformInfo(platform[i], CL_PLATFORM_VENDOR, size, str, NULL);
		printf("Vendor		%s \n", str);
		err = clGetPlatformInfo(platform[i], CL_PLATFORM_PROFILE, size, str, NULL);
		printf("Profile		%s \n", str);
		err = clGetPlatformInfo(platform[i], CL_PLATFORM_EXTENSIONS, size, str, NULL);
		printf("\nPlatform extensions \n%s \n", str);
	}
}

void PrintDeviceInfo(cl_device_id device)
{
	cl_int err;
	char name[512];
	cl_uint unit;
	cl_uint freq;
	cl_ulong gSize;
	cl_int gCacheLine;
	char ver[512];
	char ext[1024];

	err = clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(name), name, NULL);
	printf("\nDevice			%s \n", name);
	err = clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &unit, NULL);
	printf("Compute unit number	%d \n", unit);
	err = clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &freq, NULL);
	printf("Device frequency	%d MHz\n", freq);
	err = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &gSize, NULL);
	printf("Global size		%0.0f MB\n", (float)(gSize/1024/1024));
	err = clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE, sizeof(cl_uint), &gCacheLine, NULL);
	printf("Global CacheLine	%d   Byte\n", gCacheLine);
	err = clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof(ver), ver, NULL);
	printf("Version			%s \n", ver);
	err = clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(unit), &unit, NULL);
	printf("=evice dim		%d \n", unit);
	err = clGetDeviceInfo(device, CL_DEVICE_EXTENSIONS, sizeof(ext), ext, NULL);
	printf("\nDevice extentions\n%s \n", ext);

}

void PrintContextInfo(cl_context context)
{
	cl_int err;
	cl_uint numDev;
	err = clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES, sizeof(cl_uint), &numDev, NULL);
	cl_device_id* devInContext = (cl_device_id*)malloc(numDev * sizeof(cl_device_id));
	printf("\nContext has %d device(s)\n", numDev);
	err = clGetContextInfo(context, CL_CONTEXT_DEVICES, numDev * sizeof(cl_device_id), devInContext, NULL);
	for (int i = 0; i < numDev; i++)
	{
		printf("Device[%d]\n", i);
		PrintDeviceInfo(*devInContext);
	}
}

void PrintBuildLog(cl_program program, cl_device_id device)
{
	cl_int err;
	printf("\nBuild Log :\n");
	char log[2048];
	err = clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, sizeof(log), log, NULL);
	printf("%s", log);
}

void PrintKernelInfo(cl_kernel kernel, cl_device_id device)
{
	cl_int err = 0;
	char str[256];
	size_t tmp;
	clGetKernelInfo(kernel, CL_KERNEL_FUNCTION_NAME, sizeof(str), str, NULL);
	printf("\nKernel name	%s\n", str);
	clGetKernelWorkGroupInfo(kernel, device, CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE, sizeof(size_t), &tmp, NULL);
	printf("Prefered size	%zd\n", tmp);
}