#include<stdio.h>
#include<string.h>

int my_strcmp(const char* arr1,const char* arr2)
{
	int i = 0;
	
	while (arr1[i] == arr2[i]&&arr1[i]!=0)
	{
		i++;
	}
	if (arr1[i] > arr2[i])
		return 1;
	else if (arr1[i] < arr2[i])
		return -1;
	else
		return 0;
}

int main()
{
	char arr1[20] = "xielicheng";
	char arr2[20] = "xielicheng";
	int a = strcmp(arr1, arr2);
	if (a > 0)
		printf("arr1>arr2\n");
	else if (a < 0)
		printf("arr1<arr2\n");
	else
		printf("arr1==arr2\n");
	int b = my_strcmp(arr1, arr2);
	if (b > 0)
		printf("arr1>arr2\n");
	else if (b < 0)
		printf("arr1<arr2\n");
	else
		printf("arr1==arr2\n");
	return 0;
}