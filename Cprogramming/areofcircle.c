#include <stdio.h>
int main()
 {
    float pi=3.14,r,area;
    printf("Enter radius of circle: ");
    scanf("%f", &r);
    area = pi * r * r;
    printf("Area in floating format: %.2f\n", area);
    printf("Area in exponential format: %.2e\n", area);
    return 0;
}
