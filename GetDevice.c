#include"OpenCLCommon.h"

cl_device_id* GetDevice(cl_uint numPlatform, cl_platform_id* platform, int* platformIndex, cl_uint* numDevice, int deviceType)
{
	int i = 0;
	cl_int err;
	cl_device_id* device = NULL;
	if (deviceType == CPU)
	{
		for (i = 1/*0*/; i < numPlatform; i++)
		{
			err = clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_CPU, 0, NULL, numDevice);
			if (err != CL_SUCCESS)
			{
				continue;
			}
			else
			{
				printf("\nCPU device found on platform[%d]\n", i);
				device = (cl_device_id*)malloc(*numDevice * sizeof(cl_device_id));
				err = clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_CPU, *numDevice, device, NULL);
				CheckErr(err, __LINE__);
				break;
			}
		}
	}
	else if (deviceType == GPU)
	{
		for (i = 0; i < numPlatform; i++)
		{
			err = clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_GPU, 0, NULL, numDevice);
			if (err != CL_SUCCESS)
			{
				continue;
			}
			else 
			{
				printf("\nGPU device found on platform[%d]\n", i);
				device = (cl_device_id*)malloc(*numDevice * sizeof(cl_device_id));
				err = clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_GPU, *numDevice, device, NULL);
				CheckErr(err, __LINE__);
				break;
			}
		}
	}
	*platformIndex = i;
	return device;
}