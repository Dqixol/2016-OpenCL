#ifndef CL_COMMON_H
#define CL_COMMON_H

#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include<OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif // __APPLE__

#define CPU 0
#define GPU 1
#define ACC 2

void CheckErr(cl_int err, int num);

char* ReadKernelSourceFile(const char* filename, size_t *length);

cl_platform_id* GetPlatform(cl_uint* numPlatform);

void PrintPlatformInfo(cl_platform_id* platform, cl_uint numPlatform);

cl_device_id* GetDevice(cl_uint numPlatform, cl_platform_id* platform, int* platformIndex, cl_uint* numDevice, int deviceType);

void PrintDeviceInfo(cl_device_id device);

cl_context CreateContext(cl_platform_id* platform, int platformIndex, cl_device_id* device, cl_uint numDevice);

void PrintContextInfo(cl_context context);

cl_command_queue CreateCmdQueue(cl_context context, cl_device_id device);

size_t* SaveProgramToBinary(cl_program program, const char* OutFileName);

void PrintBuildLog(cl_program program, cl_device_id device);

void PrintKernelInfo(cl_kernel kernel, cl_device_id device);

void Clean(cl_context context, cl_command_queue cmdQueue, cl_program program, cl_kernel kernel);

#endif
