#include <stdio.h>
int main()
{
	int a, b, c;
	int sum;
	int avg;
	printf("Enter first number: ");
	scanf("%d", &a);
	printf("Enter second number: ");
	scanf("%d", &b);
	printf("Enter third number: ");
	scanf("%d", &c);
	sum = a + b + c;
	avg = (a + b + c)/3;
	printf("sum= %d\n", &sum);	
	printf("avg= %d", &avg);	
	return 0;	
}
