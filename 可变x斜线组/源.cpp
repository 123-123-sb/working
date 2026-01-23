#include<stdio.h>

int main()
{
	int a = 0;
	puts("input");
	scanf_s("%d", &a);
	int i = 0;
	for (i = 1; i <= a; i++)
	{
		int k = 1;
		for (k = 1; k <= a; k++)
		{
			if (k == i || k == (a + 1 - i))
				printf("*");
			else
				printf(" ");
		}
		puts("");
	}
	return 0;
}