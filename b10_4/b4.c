#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define ONE_K (1024)
static const char *AUTHOR =
    "Author: BigShark | Copyright 2025";

int main()
{
	puts(AUTHOR);
	char *some_memory;
	char *scan_ptr;
	int count = 1;

	some_memory = (char *)malloc(ONE_K);

	if(some_memory == NULL)
	{
		exit(EXIT_FAILURE);
	}

	scan_ptr = some_memory;

	while(1)
	{
		*scan_ptr = '\0';
		printf("Write byte %d\n", count);
		fflush(stdout);
		scan_ptr++;
		count++;

		usleep(10000);
	}

	exit(EXIT_SUCCESS);
}
