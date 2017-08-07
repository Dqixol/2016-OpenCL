#include"DataProcess.h"

struct VideoData** ReadCSV(size_t lineCount, char* fileName)
{
	FILE* fp = fopen(fileName, "r");

	struct VideoData **Data = NULL;
	size_t size = (lineCount) * sizeof(struct VideoData*);
	Data = (struct ViceoData**)malloc(size);

	for (size_t i = 0; i < lineCount; i++)
	{
		Data[i] = (struct ViceoData*)malloc(sizeof(struct VideoData));
		struct VideoData* tmp = Data[i];
		fscanf(fp, "%ld,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
			&(tmp->IDs),
			&(tmp->ISP),
			&(tmp->E2ERTT),
			&(tmp->PAS),
			&(tmp->ID),
			&(tmp->PR),
			&(tmp->VMOS),
			&(tmp->TAS),
			&(tmp->PST),
			&(tmp->PLT),
			&(tmp->TT),
			&(tmp->PC),
			&(tmp->CS),
			&(tmp->IDA),
			&(tmp->SQ),
			&(tmp->SL),
			&(tmp->SS));
	}
	
	fclose(fp);
	return Data;
}

size_t GetLineCount(char* fileName)
{
	size_t lineRet = 0;
	char tmp = 1;
	lineRet = 0;
	FILE* fp = fopen(fileName, "r");
	while (tmp >= 0)
	{
		tmp = fgetc(fp);
		if (tmp == '\n')
			lineRet++;
	}
	fclose(fp);
	return lineRet;
}