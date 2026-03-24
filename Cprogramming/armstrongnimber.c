#include <stdio.h>
#include <math.h>

// Function to check if a number is Armstrong
int isArmstrong(int num) {
    int original, remainder, result = 0, n = 0;
    original = num;

    // Count number of digits
    while(original != 0) {
        original /= 10;
        n++;
    }

    original = num;
    // Calculate the sum of digits each raised to the power n
    while(original != 0) {
        remainder = original % 10;
        result += pow(remainder, n);
        original /= 10;
    }

    // Check if number is Armstrong
    if(result == num)
        return 1;
    else
        return 0;
}

int main() {
    int i;

    printf("Armstrong numbers from 1 to 100:\n");
    for(i = 1; i <= 100; i++) {
        if(isArmstrong(i))
            printf("%d ", i);
    }
    printf("\n");
    return 0;
}
