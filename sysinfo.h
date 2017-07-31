#ifndef SYSINFO_H
#define SYSINFO_H
#include<stdio.h>
#include<stdlib.h>
#ifdef _APPLE_
#include<OpenCL/OpenCL.h>
#else
#include<CL/cl.h>
#endif
void sysinfo();
#endif // !SYSINFO_H
