#include <stdio.h>

int main() {
    float num1, num2, result;
    char operator;

    // Input two operands and one operator
    printf("Enter first number: ");
    scanf("%f", &num1);

    printf("Enter second number: ");
    scanf("%f", &num2);

    printf("Enter an operator (+, -, *, /): ");
    scanf(" %c", &operator);

    // Perform operation using switch
    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("Result: %.2f\n", result);
            break;
        case '-':
            result = num1 - num2;
            printf("Result: %.2f\n", result);
            break;
        case '*':
            result = num1 * num2;
            printf("Result: %.2f\n", result);
            break;
        case '/':
            if (num2 != 0)
                result = num1 / num2;
            else {
                printf("Error: Division by zero\n");
                return 1;
            }
            printf("Result: %.2f\n", result);
            break;
        default:
            printf("Error: Invalid operator\n");
    }

    return 0;
}
