#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>

/*
      ***        ***      1
    *******    *******    2
   ********************   3
   ********************   4
    ******************    5
      **************      6
	    **********        7
	      ******          8
		    **            9
*/
int main()
{
	puts("everydays work make you get to better yourself");
	int i=0;
	int a = i%9;
	for (i = 0;; i++)
	{
			int a = i%10;
			switch (a)
			{
			case 0:
				printf("    ***        ***\n");
				break;
			case 1:
				printf("  *******    *******\n");
				break;
			case 2:
				printf(" ********************\n");
				break;
			case 3:
				printf(" ********************\n");
				break;
			case 4:
				printf("  ******************\n");
				break;
			case 5:
				printf("    **************\n");
				break;
			case 6:
				printf("      **********\n");
				break;
			case 7:
				printf("        ******\n");
				break;
			case 8:
				printf("          **\n");
				break;
			case 9:
				system("cls");
				break;
			}
			Sleep(10);
	}
		
	
	return 0;
}