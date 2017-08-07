#include"OpenCLCommon.h"
#include"DataProcess.h"

int main()
{

	cl_int err;
	int platformIndex;
	cl_uint numPlatform;
	cl_uint numDevice;

	cl_platform_id* platform = GetPlatform(&numPlatform);
	//PrintPlatformInfo(platform, numPlatform);

	cl_device_id* device = GetDevice(numPlatform, platform, &platformIndex, &numDevice, GPU);
	PrintDeviceInfo(*device);

	cl_context context = CreateContext(platform, platformIndex, device, numDevice);
	//PrintContextInfo(context);

	cl_command_queue CmdQueue = CreateCmdQueue(context, *device);

	size_t sourceLen;
	char* source = ReadKernelSourceFile("C:\\Users\\dqico\\Documents\\Visual Studio 2017\\Projects\\Project1\\Project1\\learn.cl",&sourceLen);
	cl_program program = clCreateProgramWithSource(context, 1, &source, &sourceLen, &err);
	CheckErr(err, __LINE__);
	err = clBuildProgram(program, 1, device, NULL, NULL, NULL);
	CheckErr(err, __LINE__);
	PrintBuildLog(program, *device);
	
	cl_kernel kernel = clCreateKernel(program, "learn", &err);
	CheckErr(err, __LINE__);
	PrintKernelInfo(kernel, *device);

	size_t offset[2] = { 3,5 };
	size_t glbSize[2] = { 6,4 };
	size_t lclSize[2] = { 3,2 };
	err = clEnqueueNDRangeKernel(CmdQueue, kernel, 2, offset, glbSize, lclSize, 0, NULL, NULL);
	CheckErr(err, __LINE__);

	//size_t lineCount = GetLineCount("C:\\Users\\dqico\\Documents\\Visual Studio 2017\\Projects\\Project1\\Project1\\data.txt");
	//struct VideoData** Data = NULL;
	//Data = ReadCSV(lineCount, "C:\\Users\\dqico\\Documents\\Visual Studio 2017\\Projects\\Project1\\Project1\\data.txt");
	Clean(context, CmdQueue, program, kernel);
	getchar();
}