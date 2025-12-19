long long tinh_tich(int a[], int n)
{
	long long nhan = 1;
	for(int i=0; i<n; i++)
	{
		nhan*=a[i];
	}
	return nhan;
}
