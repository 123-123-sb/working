#include<stdio.h>
#include<string.h>

char* my_strstr(char*arr1,const char*arr2)
{
	int len1 = strlen(arr1);
	int len2 = strlen(arr2);
	if (*arr2 == '\0' || len2 > len1)
		return NULL;
	int i=0;
	while (*(arr1+i)!='\0')
	{
		if (*(arr1 + i) == *arr2)
		{
			char* p = (arr1 + i);
			int j = 0;
			for (j = 0;; j++)
			{
				if (*(arr1 + i + j) != '0' && *(arr2 + j) != '0')
				{
					if (*(arr1 + i + j) != *(arr2 + j))
						break;
					if (j == len2 - 1)
						return p;
				}

			}
		}
		i++;
	}
}

int main()
{
	char arr1[70] = "tommorow always be better so dont give up because difficulty today";
	char arr2[] = "give up";
	char arr3[] = "just do it";
	char* p1 = my_strstr(arr1, arr3);
	printf("%s", p1);
	return 0;
}