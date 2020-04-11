#include "common.h"

void logger(char* file, char* info)
{
	FILE* input = fopen(file, "w");
	if (input == NULL)
	{
		printf("Could not open file");
		return;
	}

	fprintf(input, "%s\n", info);
	
	fclose(input);
}