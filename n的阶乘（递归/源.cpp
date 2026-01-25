#include<stdio.h>

int calculate(int n)
{
	if (n > 1)
	{
		return n * calculate(n - 1);
	}
	else if (n == 1 || n == 0)
	{
		return 1;
	}
	else
		return 0;
}

int main()
{
	int n = 0;
	puts("give a number in it");
	scanf_s("%d", &n);
	int result = calculate(n);
	if (result == 0)
		puts("input miataken");
	else
	    printf("%d", result);
    return 0;
}