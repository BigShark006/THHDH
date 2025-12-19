#include <stdio.h>

long long tinh_tong(int a[], int n);
long long tinh_tich(int a[], int n);

#define MAX 100

int main()
{
	int a[100], n;
	
	printf("Nhap so phan tu: "); scanf("%d", &n);

	for(int i=0; i<n; i++)
	{
		printf("a[%d] = ", i); scanf("%d", &a[i]);
	}

	long long tong = tinh_tong(a,n);
	long long nhan = tinh_tich(a,n);

	printf("Tong cua cac phan tu la: %lld\n", tong);
	printf("\n");
	printf("\nTich cua cac phan tu la: %lld", nhan);

	return 0;
}
