#include<stdio.h>

int cal(int a)
{
	int x = 0;
	int i = 10;
	for (i=10;a/i>0;i=i*10)
	{
		x = x + (a / i) * (a % i);
	}
	if (x == a)
		return 1;
	else
	    return 0;
}

int main()
{
	puts("input>1");
	int a = 0;
	scanf_s("%d", &a);
	int result = 0;
	int i = 0;
	int range = 1;
	for (i = 0; i < a-1; i++)
	{
		range = range * 10;
	}
	int k = 10 * range;
	for (; range < k; range++)
	{
		int b = cal(range);
		if (b == 1)
			result++;
	}
	printf("result is %d", result);
	return 0;
}