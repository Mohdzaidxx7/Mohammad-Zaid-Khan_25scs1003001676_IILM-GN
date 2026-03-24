#include <stdio.h>

int reverseNumber(int n)
{

    int result = 0;

    while (n)
    {
        int digit = n % 10;
        result = result * 10 + digit;
        // n = n / 10
        n /= 10;
    }

    return result;
}

int main()
{

    int num;

    printf("Enter the number: ");
    scanf("%d", &num);

    printf("Reversed Number: %d", reverseNumber(num));

    printf("\n");
    return 0;
}