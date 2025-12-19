#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Thuc thi lenh ps voi execlp\n");
	execlp("ps", "ps", "-ax", 0);
	printf("Thuc hien xong! Ban se khong thay tien trinh nay!\n");
	exit(0);
}
