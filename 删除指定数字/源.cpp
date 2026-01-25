#include<stdio.h>

int main()
{
    int i = 0;
    int a = 0;
    int b = 0;
    puts("how many numbers do you want");
    scanf_s("%d", &a);      
    puts("next");
    int arr1[50] = { 0 };
    int arr2[50];
    for (i = 0; i < a; i++)
    {
        scanf_s("%d", &arr1[i]);
    }
    puts("input the order of the number what you want to delete");
    scanf_s("%d", &b);
    for (i = 0; i < b; i++)
    {
        arr2[i] = arr1[i];
    }
    for (i = b; i < a; i++)
    {
        arr2[i-1] = arr1[i];
    }
    puts("the result");
     for (i = 0; i < a-1; i++)
    {
        printf("%d  ", arr2[i]);
    }
    return 0;
}