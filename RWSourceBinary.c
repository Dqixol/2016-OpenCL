#include "OpenCLCommon.h"
char* ReadKernelSourceFile(const char* filename, size_t *lengthRet)
{
    FILE *file = NULL;
    size_t sourceLength;
    char* sourceString;
    size_t ret;
    file = fopen(filename, "rb");
    if(file == NULL)
    {
        printf("%s cannot be open\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    sourceLength = ftell(file);
    fseek(file, 0, SEEK_SET);
    sourceString = (char*)malloc(sourceLength + 1);
    sourceString[0] = '\0';
    ret = fread(sourceString,sourceLength,1,file);
    if(ret == 0)
    {
        printf("%s cannot be read", filename);
        return NULL;
    }
    fclose(file);
    if(sourceLength != 0)
    {
        *lengthRet = sourceLength;
    }
    sourceString[sourceLength] = '\0';
    return sourceString;
}

size_t* SaveProgramToBinary(cl_program program, const char* outFileName)
{
	cl_int err;
	cl_uint numDevice;
	err = clGetProgramInfo(program, CL_PROGRAM_NUM_DEVICES, sizeof(cl_uint), &numDevice, NULL);
	cl_device_id* device = (cl_device_id*)malloc(numDevice * sizeof(cl_device_id));
	err = clGetProgramInfo(program, CL_PROGRAM_DEVICES, sizeof(numDevice * sizeof(cl_device_id)), device, NULL);
	size_t *binSize = (size_t*)malloc(sizeof(size_t) * numDevice);
	err = clGetProgramInfo(program, CL_PROGRAM_BINARY_SIZES, sizeof(sizeof(size_t) * numDevice), binSize, NULL);
	unsigned char** programBin = (unsigned char**)malloc(sizeof(unsigned char) * numDevice);
	for (size_t i = 0; i < numDevice; i++)
	{
		programBin[i] = (unsigned char**)malloc(sizeof(unsigned char) * binSize[i]);
	}
	err = clGetProgramInfo(program, CL_PROGRAM_BINARIES, numDevice * sizeof(unsigned char*), programBin, NULL);
	for (size_t i = 0; i < numDevice; i++)
	{
		FILE *fp = fopen(outFileName, "a+");
		fwrite(programBin[i], 1, binSize[i], fp);
		fclose(fp);
	}
	return binSize;
}