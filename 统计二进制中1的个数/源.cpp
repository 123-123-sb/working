#include<stdio.h>

int judge(int a)
{
	int result = 0;
	if (a >= 0)
	{
		while (a != 0 || a % 2!= 0)
		{
			result=result+a % 2;
			a = a / 2;
		}
		return result;
	}
	else
	{
		int b = a ^(-1);
		int result = 0;
		while (b != 0 || b%2 != 0)
		{
		    result = result + b % 2;
			b = b / 2;
		}
		return (32 - result);
	}
}

int main()
{
	int a = 0;
	scanf_s("%d", &a);
	int b = judge(a);
	printf("%d", b);
	return 0;
}