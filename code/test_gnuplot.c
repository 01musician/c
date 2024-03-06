#include <stdio.h>
#include <math.h>

#define NUM_POINTS 100
// gcc -o test_gnuplot test_gnuplot.c -lm
int main() {
    FILE *fp;
    double x, y;

    // Open a file for writing
    fp = fopen("data.txt", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Generate data points (x, sin(x)) and write them to the file
    for (int i = 0; i < NUM_POINTS; i++) {
        x = i * 0.1;  // Generate x values from 0 to 10
        y = sin(x);   // Calculate corresponding y values
        fprintf(fp, "%lf %lf\n", x, y);  // Write (x, y) pair to file
    }

    // Close the file
    fclose(fp);

    return 0;
}

