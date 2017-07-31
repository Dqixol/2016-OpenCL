#include"sysinfo.h"
#include<time.h>

const char* programSource =
"__kernel                                            \n"
"void vecadd(__global int *A,                        \n"
"            __global int *B,                        \n"
"            __global int *C)                        \n"
"{                                                   \n"
"                                                    \n"
"   // Get the work-items unique ID                  \n"
"   int idx = get_global_id(0);                      \n"
"                                                    \n"
"   // Add the corresponding locations of            \n"
"   // 'A' and 'B', and store the result in 'C'.     \n"
"   C[idx] = A[idx] * B[idx];                        \n"
"}                                                   \n"
;

int main()
{
	sysinfo();
	const int elements = 2048;
	size_t datasize = elements * sizeof(int);
	char str[512] = { 0 };

	cl_int errors = 0;
	cl_platform_id *platforms = NULL;
	cl_uint num_platforms = 0;
	cl_uint numDevice[2] = { 0, 0 };
	cl_device_id *devices[2] = { NULL,NULL };
	cl_device_type devicetype;
	cl_long tmp;

	//create data on host
	int *A = (int*)malloc(datasize), *B = (int*)malloc(datasize), *C = (int*)malloc(datasize);
	for (int i = 0; i < elements; i++) {
		A[i] = i;
		B[i] = i;
		C[i] = 0;
	}

	//platform info discover
	errors = clGetPlatformIDs(0, platforms, &num_platforms);
	platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id) * num_platforms);
	errors = clGetPlatformIDs(num_platforms, platforms, NULL);

	//device info gather
	for (cl_int i = 0; i < num_platforms; i++)
	{
		//get each platform device info 
		errors = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevice[i]);
		devices[i] = (cl_device_id*)malloc(numDevice[i] * sizeof(cl_device_id));
		errors = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, numDevice[i], devices[i], NULL);
	}

	//create a context
	cl_context context = clCreateContext(NULL, numDevice[1], devices[1], NULL, NULL, &errors);

	//create a command queue
	cl_command_queue cmdQueue = clCreateCommandQueueWithProperties(context, devices[1][0], 0, &errors);

	//get the device in this queue
	cl_device_id *devv = NULL;
	devv = (cl_device_id*)malloc(sizeof(cl_device_id) * 2);
	errors = clGetCommandQueueInfo(cmdQueue, CL_QUEUE_DEVICE, sizeof(cl_device_id), devv, NULL);

	//show the que device type
	errors = clGetDeviceInfo(*devv, CL_DEVICE_NAME, 512, str, NULL);
	printf("\nrunning on \t\t%s\n", str);

	//create buffer on context
	cl_mem bufferA, bufferB, bufferC;
	bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, &errors);
	bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY, datasize, NULL, &errors);
	bufferC = clCreateBuffer(context, CL_MEM_WRITE_ONLY, datasize, NULL, &errors);

	//write A B to devices
	errors = clEnqueueWriteBuffer(cmdQueue, bufferA, CL_FALSE, 0, datasize, A, 0, NULL, NULL);
	errors = clEnqueueWriteBuffer(cmdQueue, bufferB, CL_FALSE, 0, datasize, B, 0, NULL, NULL);

	//create program with source
	cl_program program = clCreateProgramWithSource(context, 1, &programSource, NULL, &errors);

	//compile the program
	errors = clBuildProgram(program, numDevice[1], devices[1], NULL, NULL, NULL);

	//create kernel 
	cl_kernel kernel = clCreateKernel(program, "vecadd", &errors);

	//set kernel args 
	errors = clSetKernelArg(kernel, 0, sizeof(cl_mem), &bufferA);
	errors = clSetKernelArg(kernel, 1, sizeof(cl_mem), &bufferB);
	errors = clSetKernelArg(kernel, 2, sizeof(cl_mem), &bufferC);

	//define index space of work items for exeuate
	size_t globalWorkSize = elements;

	//execuate the kernel on devices
	clock_t tstart = clock();
	errors = clEnqueueNDRangeKernel(cmdQueue, kernel, 1, NULL, &globalWorkSize, NULL, 0, NULL, NULL);

	//read bufferC from device
	errors = clEnqueueReadBuffer(cmdQueue, bufferC, CL_TRUE, 0, datasize, C, 0, NULL, NULL);

	clock_t tend = clock();
	printf("Elaspsed in %1.10lf s\n", (double)(tend - tstart) / CLOCKS_PER_SEC);

	clReleaseKernel(kernel);
	clReleaseProgram(program);
	clReleaseCommandQueue(cmdQueue);
	clReleaseMemObject(bufferA);
	clReleaseMemObject(bufferB);
	clReleaseMemObject(bufferC);
	clReleaseContext(context);

	free(A);
	free(B);
	free(C);
	free(platforms);
	free(devices[1]);
	free(devices[0]);
	free(devv);
	getchar();
}