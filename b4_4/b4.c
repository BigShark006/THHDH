#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	int child_status;
	int n;
	pid=fork();
	switch(pid)
	{
		case -1:
			printf("Khong the tao tien trinh moi");
			exit(1);
		case 0:
			n=0;
			for( ;n<5;n++)
			{
				printf("Tien trinh con  ");
				sleep(1);
			}
			exit(0);
		default:
			printf("Tien trinh cha, cho tien trinh con hoan thanh\n");
			wait(&child_status);
			printf("\nTien trinh cha - tien trinh con hoan thanh\n");
	}
	return 0;
}
