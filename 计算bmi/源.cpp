#include<stdio.h>
int main()
{
	int kg ;
	int cm ;
	puts("give your weight(KG) and hight(CM) in it");
	scanf_s("%d %d", &kg, &cm);
	float BMI =10000* kg / cm / cm;
	printf("your BMI\n%.3f\n", BMI);
	puts("dont let your lazy behaivour defeat your mind");
	return 0;
}