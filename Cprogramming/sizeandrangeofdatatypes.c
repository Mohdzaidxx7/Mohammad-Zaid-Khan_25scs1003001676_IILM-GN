#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    printf("---- Integer Data Types ----\n");
    printf("Size of int: %lu bytes\n", sizeof(int));
    printf("Range of int: %d to %d\n", INT_MIN, INT_MAX);

    printf("\nSize of short int: %lu bytes\n", sizeof(short int));
    printf("Range of short int: %d to %d\n", SHRT_MIN, SHRT_MAX);

    printf("\nSize of long int: %lu bytes\n", sizeof(long int));
    printf("Range of long int: %ld to %ld\n", LONG_MIN, LONG_MAX);

    printf("\nSize of unsigned int: %lu bytes\n", sizeof(unsigned int));
    printf("Range of unsigned int: 0 to %u\n", UINT_MAX);

    printf("\n---- Character Data Type ----\n");
    printf("Size of char: %lu bytes\n", sizeof(char));
    printf("Range of char: %d to %d\n", CHAR_MIN, CHAR_MAX);

    printf("\n---- Floating Point Data Types ----\n");
    printf("Size of float: %lu bytes\n", sizeof(float));
    printf("Range of float: %e to %e\n", FLT_MIN, FLT_MAX);

    printf("\nSize of double: %lu bytes\n", sizeof(double));
    printf("Range of double: %le to %le\n", DBL_MIN, DBL_MAX);

    return 0;
}
