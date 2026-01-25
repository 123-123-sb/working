#include<stdio.h>
int main()
{
	char str[100] = { 0 };
	puts("intput chars in it");
	int i = 0;
	for (i = 0; i < 100; i++)
	{
		scanf_s("%c", &str[i]);
		if (str[i] == '\n')
			break;
	}
	char str2[100] = { 0 };
	for (i = 0; i < 100; i++)
	{
		str2[99-i] = str[i];
		if (str[i] == '\n')
			break;
	}
	for (i = 0; i < 100; i++)
	{
		printf("%c", str2[i]);
	}
	return 0;
}