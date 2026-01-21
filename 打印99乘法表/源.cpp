#include<stdio.h>
int main()
{
	int a = 1;
	int b = 1;
	for (a = 1; a < 10; a++)
	{
		for (b = 1; b <= a; b++)
		{
			if (a == b)
				printf("%d*%d\n",a,b);
			else
				printf("%d*%d  ",a,b);
		}
		
	}
	return 0;
}