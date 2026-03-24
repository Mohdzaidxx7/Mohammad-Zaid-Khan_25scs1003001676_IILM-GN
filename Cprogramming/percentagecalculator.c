#include <stdio.h>

int main() {
    int marks[5];
    int i;
    float sum = 0, percentage;
    
    // Input marks for five subjects
    printf("Enter marks for five subjects:\n");
    for (i = 0; i < 5; i++) {
        scanf("%d", &marks[i]);
        sum += marks[i];
    }
    
    // Calculate percentage
    percentage = (sum / 5);

    // Print the grade
    printf("Percentage: %.2f%%\n", percentage);

    if (percentage >= 90 && percentage <= 100) {
        printf("Grade: A\n");
    } else if (percentage >= 80 && percentage < 90) {
        printf("Grade: B\n");
    } else if (percentage >= 60 && percentage < 80) {
        printf("Grade: C\n");
    } else {
        printf("Grade: D\n");
    }

    return 0;
}
