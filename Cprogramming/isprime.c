#include <stdio.h>

int isPrime(int n)
{

    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{

    int num;

    printf("Enter the number: ");
    scanf("%d", &num);

    if (isPrime(num))
    {
        printf("%d it is a prime number", num);
    }
    else
    {
        printf("%d Not a prime number", num);
    }

    printf("\n");
    return 0;
}