#include<stdio.h>
int main()
{
	int a = 0;
	int n = 0;
	puts("ÊıÖµ");
	scanf_s("%d", &a);
	puts("½×Êı");
	scanf_s("%d", &n);
	int key = 1;
	int result = 0;
	int i = 0;
	for (i=0;i<n;i++)
	{
		result = result + key;
		key = key * 10 + 1;
	}
	printf("%d", result);
	return 0;
}