#include"OpenCLCommon.h"
cl_command_queue CreateCmdQueue(cl_context context, cl_device_id device)
{
	cl_int err;
	//cl_queue_properties properties[] = { CL_QUEUE_PROPERTIES,CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE | CL_QUEUE_ON_DEVICE | CL_QUEUE_ON_DEVICE_DEFAULT,0 };
	cl_queue_properties *properties = NULL;
	cl_command_queue CmdQueue = clCreateCommandQueueWithProperties(context, device, properties, &err);
	CheckErr(err, __LINE__);
	return CmdQueue;
}