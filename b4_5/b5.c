#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	pid_t pid;
	int child_status;
	int n;
	pid = fork();
	switch(pid)
	{
		case -1:
			printf("Khong the tao tien trinh moi\n");
			exit(1);
		case 0:
			n=0; 
			for( ;n<5;n++)
			{
				printf("Tien trinh con  ");
				sleep(1);
			}
			exit(37);
		default:
			n=3;
			for( ;n>0; n--)
			{
				printf("Tien trinh cha  ");
				sleep(1);
			}
			wait(&child_status);
			printf("Tien trinh con hoan thanh: PID = %d\n", pid);
			if(WIFEXITED(child_status))
				printf("Tien trinh con thoat ra voi ma %d\n", WEXITSTATUS(child_status));
			else
				printf("Tien trinh con ket thuc binh thuong\n");
			break;
	}
	exit(0);
}
