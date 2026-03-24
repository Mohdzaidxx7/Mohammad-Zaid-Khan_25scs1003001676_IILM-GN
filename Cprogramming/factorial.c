#include <stdio.h>

int main() 
{
    int n, i;
    unsigned long long factorial = 1;

    // Input the number
    printf("Enter a number: ");
    scanf("%d", &n);

    // Calculate factorial using a loop
    if (n < 0) {
        printf("Factorial does not exist for negative numbers.\n");
    } else {
        for(i = 1; i <= n; i++) {
            factorial *= i;
        }
        printf("Factorial of %d is %llu\n", n, factorial);
    }

    return 0;
}
