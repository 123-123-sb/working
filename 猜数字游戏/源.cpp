#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
void menu2()
{
	puts("do you want to play it again?");
	printf("****************************\n");
	printf("****press 1 restart it *****\n");
	printf("****press any to end it ****\n");
	printf("****************************\n");
}

void menu()
{
	printf("*****************************\n");
	printf("********choose 1 play *******\n");
	printf("********choose 0 exit *******\n");
	printf("*****************************\n");
}

void game()
{
	int key = rand() % 100 + 1;
	//printf("%d\n", key);
	puts("guess the number from 1 to 100");
	int guess = 0;
	do
	{
		scanf_s("%d", &guess);
		if (guess < key)
		{
			puts("your guess is too little");
			continue;
		}
		if (guess > key)
		{
			puts("your guess is too big");
			continue;
		}
		else
		{
			system("cls");
			puts("guess correctly");
			printf("answer is %d\n", key);
			break;
		}
	} while (guess<key || guess>key);
}

int main()
{
	int choice = 0;
	int input = 0;
	srand((unsigned int)time(NULL));

	do
	{
		puts("make your choice for the game");
		menu();
	    scanf_s("%d", &input);
		system("cls");
		switch (input)
		{
		case 0:
			printf("game over\n");
			break;
		case 1:
			printf("begin the game\n");
			game();
			menu2();
			scanf_s("%d", &choice);
			system("cls");
			if (choice == 1)
			 continue;
		
			else
				break;
			break;
		default:
			puts("incorrect input");
			break;

		}
	} while (input == 1);
	puts("maybe work every days tasks are so diffcult and boring");
	puts("However,every effort will always gain");
	return 0;
}