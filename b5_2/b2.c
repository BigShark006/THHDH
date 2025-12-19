#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void do_child(int data_pipes[])   //Cai dat ham thuc thi tien trinh con
{
	int c, rc;
	close(data_pipes[1]);
	while((rc = read(data_pipes[0], &c, 1))>0)
	{
		putchar(c);
	}
	exit(0);
}

void do_parent(int data_pipes[])    //Cai dat ham xu ly cong viec cua tien trinh cha
{
	int c, rc;
	close(data_pipes[0]);
	while((c = getchar() ) > 0)
	{
		rc = write(data_pipes[1], &c, 1);
		if(rc == -1)
		{
			perror("Parent: pipe write error");
			close(data_pipes[1]);
			exit(1);
		}
	}
	close(data_pipes[1]);
	exit(0);
}

int main()
{
	int data_pipes[2];
	int pid, rc;

	rc=pipe(data_pipes);
	if(rc==-1)
	{
		perror("Error: pipe not created");
		exit(1);
	}
	pid=fork();
	switch(pid)
	{
		case -1:
			perror("Child process not created");
			exit(1);
		case 0:
			do_child(data_pipes);
		default:
			do_parent(data_pipes);
	}
	return 0;
}
