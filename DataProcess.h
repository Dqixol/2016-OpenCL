#ifndef DATA_PROCESS_H
#define DATA_PROCESS_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct VideoData
{
	long	IDs;	//identifier
	float	ISP;
	float	E2ERTT;
	float	PAS;
	float	ID;		//Initial delay
	float	PR;		//pause ratio;
	float	VMOS;
	float	TAS;
	float	PST;
	float	PLT;
	float   TT;
	float	PC;
	float	CS;
	float	IDA;
	float	SQ;
	float	SL;
	float	SS;
};

struct VideoData** ReadCSV(size_t lineCount, char* fileName);

size_t GetLineCount(char* fileName);

#endif
