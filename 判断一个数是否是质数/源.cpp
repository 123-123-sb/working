#include<stdio.h>
void judge(int x)
{
	int i = 2;
	if (x < 1)
	{
		puts("invailed input");
	}
	else if (x == 1)
	{
		puts("this num isnt prime");
     }

	else if (x== 2)
	{
		printf("the number is prime\n");
	
	}
	else
	{
		int c;
		for (i = 2; i < x; i++)
		{
			int a = x % i;
			if (a == 0)
			{
				break;
			}		
		}
		if (i == x)
			puts("the number is prime");
		else
			puts("the number isnt prime");

	}

}  
int main()
{
	int num;
	puts("give a number ");
    scanf_s("%d",&num);
    judge (num);
	puts("a diligent man is always respectable!");
	return 0;
}