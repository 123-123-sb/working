#include<stdio.h>
int main()
{
	int a = 0;
	int b = 0;
	scanf_s("%d %d", &a, &b);
	while (a % b)
	{
		int c = a % b;
		a = b;
		b = c;
	}
	printf("%d", b);
	return 0;
}