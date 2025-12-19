#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	char* message;
	int n;
	pid = fork();
	switch(pid)
	{
		case -1:
			printf("Khong the tao tien trinh con!");
			exit(1);
		case 0:
			message = "Day la tien trinh con!";
			n=0;
			for( ;n<5;n++)
			{
				printf("%s", message);
				sleep(1);
			}
			break;
		default:
			message = "Day la tien trinh cha!";
			n=0;
			for( ;n<3; n++)
			{
				printf("%s", message);
				sleep(1);
			}
			break;
	}
	exit(0);
}

