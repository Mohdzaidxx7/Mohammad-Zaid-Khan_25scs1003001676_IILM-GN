#include <stdio.h>
#include <math.h>

// Function to check if a number is Armstrong
int isArmstrong(int num) {
    int temp = num, digit, sum = 0;

    // Count digits
    int digits = (num < 10) ? 1 : 2;

    while (temp > 0) {
        digit = temp % 10;
        sum += pow(digit, digits);
        temp /= 10;
    }

    if (sum == num)
        return 1;   // Armstrong
    else
        return 0;   // Not Armstrong
}

int main() {
    int i;

    printf("Armstrong numbers from 1 to 100:\n");

    for (i = 1; i <= 100; i++) {
        if (isArmstrong(i)) {
            printf("%d ", i);
        }
    }

    return 0;
}
