#include<stdio.h>
int main()
{
	int a = 0;
	puts("input a number");
	scanf_s("%d", &a);
	int arr1[16] = { 0 };
	int arr2[16] = { 0 };
	int i = 0;
	for(i=1;i<33;i++)
	{
		if (i % 2 != 0)
		{
			if ((a & 1) == 1)
			{
				arr1[i/2] = 1;
			}
			else
				arr1[i/2] = 0;
		}
		else
		{
			if ((a & 1) == 1)
			{
				arr2[(i / 2)-1] = 1;
			}
			else
				arr2[(i / 2)-1] = 0;
		}
		 a = a >> 1;
	}
	puts("奇数位");
	for (i = 1; i < 33; i++)
	{
		if(i%2!=0)
		printf("%d  ", arr1[i / 2]);
	}
	puts("");
	puts("偶数位");
	for (i = 1; i < 33; i++)
	{
		if(i%2==0)
		printf("%d  ", arr2[(i / 2)-1]);
	}
	return 0;
}