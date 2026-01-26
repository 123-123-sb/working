#include<stdio.h>
int main()
{
	int a = 0;
	int i = 0;
	char input[100];
	do
	{
	   puts("how many char do you want to input");
	   scanf_s("%d", &a);
	   if (a > 1 && a < 101)
		  break;
	} while (1);
	puts("input char in it");
	for (i = 0; i < a+1; i++)
	{
		scanf_s("%c", &input[i]);
	}
	for (i = 0; i < a+1; i++)
	{
		if (input[i] >= 'a' && input[i] <= 'z')
			printf("%c", input[i] - 32);
		else if(input[i] >= 'A' && input[i] <= 'Z')
			printf("%c", input[i] + 32);
	}
	return 0;
}