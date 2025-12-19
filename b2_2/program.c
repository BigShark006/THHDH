#include <stdio.h>

#include "cong.c"
#include "nhan.c"


int main()
{
	int a, b;
	printf("Nhap a: "); scanf("%d", &a);
	printf("Nhap b: "); scanf("%d", &b);
	printf("\nTong cua a va b la: %d ", cong(a,b));
	printf("\nNhan cua a va b la: %d ", nhan(a,b));
	return 0;
}

