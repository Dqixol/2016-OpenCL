#include"sysinfo.h"

void sysinfo()
{
	//platform info discover
	char str[512];
	cl_int errors = 0;
	cl_platform_id *platforms = NULL;
	cl_uint num_platforms = 0;
	errors = clGetPlatformIDs(0, platforms, &num_platforms);
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * num_platforms);
	errors = clGetPlatformIDs(num_platforms, platforms, NULL);

	//platform info show
	printf("num_platforms: %d\n\n", num_platforms);
	for (cl_uint i = 0; i < num_platforms; i++)
	{
		printf("[platform %d]\n", i);
		clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 512, str, NULL);
		printf("platform name \t\t[%s]\n", str);
		clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, 512, str, NULL);
		printf("platform version \t[%s]\n", str);
		clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 512, str, NULL);
		printf("platform vender \t[%s]\n", str);
		clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, 512, str, NULL);
		printf("platform profile \t[%s]\n\n", str);
	}
	//device info gather
	cl_uint numDevice[2] = { 0, 0 };
	cl_device_id *devices[2] = { NULL,NULL };
	cl_device_type devicetype;
	cl_long tmp;
	for (cl_int i = 0; i < num_platforms; i++)
	{
		//get each platform device info 
		errors = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevice[i]);
		printf("platform %d has %d divice(s)\n\n", i, numDevice[i]);
		devices[i] = (cl_device_id*)malloc(numDevice[i] * sizeof(cl_device_id));
		errors = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, numDevice[i], devices[i], NULL);
		//show each platform device info 
		for (cl_uint j = 0; j < numDevice[i]; j++)
		{
			printf("[platform %d device %d]\n", i, j);
			errors = clGetDeviceInfo(devices[i][j], CL_DEVICE_TYPE, sizeof(cl_device_type), &devicetype, NULL);
			if (devicetype == CL_DEVICE_TYPE_CPU)
				printf("device type \t\tCPU\n");
			else if (devicetype == CL_DEVICE_TYPE_GPU)
				printf("device type \t\tGPU\n");
			else if (devicetype == CL_DEVICE_TYPE_ACCELERATOR)
				printf("device type \t\tACC\n");
			errors = clGetDeviceInfo(devices[i][j], CL_DEVICE_NAME, 512, str, NULL);
			printf("device name \t\t%s\n", str);
			errors = clGetDeviceInfo(devices[i][j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_long), &tmp, NULL);
			printf("device units \t\t%ld\n", tmp);
			errors = clGetDeviceInfo(devices[i][j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_long), &tmp, NULL);
			printf("device freq \t\t%ld MHz\n\n", tmp);
		}
	}
}
