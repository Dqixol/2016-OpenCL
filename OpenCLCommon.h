#ifndef CL_COMMON_H
#define CL_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <OpenCL/OpenCL.h>

void sysinfo();

cl_context CreateContext(cl_device_id* devices);

char* ReadKernelSourceFile(const char* filename, size_t *length);

cl_command_queue CreateCmdQueue(cl_context context, cl_device_id device);

cl_program CreateProgramSource(cl_context context, cl_device_id device, const char* filename);

void Cleanup(cl_context, cl_command_queue, cl_program, cl_kernel);
#endif
