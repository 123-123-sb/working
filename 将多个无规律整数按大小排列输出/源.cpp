#include<stdio.h>
int main()
{
	
	int a = 0;
	int input[10] = { 0 };
	puts("assign values to mutiple numbers");
	for (a = 0; a < 10; a++)
	{
		scanf_s("%d", &input[a]);
	}
	for (a = 0; a < 10; a++)
	{
		int i = 0;
		for (i = a + 1; i < 10; i++)
		{
			if (input[a] >= input[i])
				continue;
			else
			{
				int b = input[a];
				input[a] = input[i];
				input[i] = b;

			}
		}
	}
	for (a = 0; a < 10; a++)
	{
		printf("%d  ", input[a]);
	}
	return 0;
}
