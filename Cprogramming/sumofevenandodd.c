#include <stdio.h>

int main() {
    int n, i;
    int even_sum = 0, odd_sum = 0;

    // Input the value of N
    printf("Enter the value of N: ");
    scanf("%d", &n);

    // Calculate sums
    for(i = 1; i <= n; i++) {
        if(i % 2 == 0)
            even_sum += i;
        else
            odd_sum += i;
    }

    // Print the results
    printf("Sum of even numbers from 1 to %d: %d\n", n, even_sum);
    printf("Sum of odd numbers from 1 to %d: %d\n", n, odd_sum);

    return 0;
}
