#include <stdio.h>

int main() {
    int n, sum = 0, i;

    // Input the number
    printf("Enter a number: ");
    scanf("%d", &n);
    // Calculate sum using a loop
    for(i = 1; i <= n; i++) {
        sum += i;
    }

    // Print the result
    printf("Sum of all numbers up to %d is %d\n", n, sum);

    return 0;
}
