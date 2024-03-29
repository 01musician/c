#include<stdlib.h>
#include<stdio.h>
#include "factorial.h"
#include "fibonacci.h"
#include "gcd.h"

int main(int argc, char **argv)
{
    printf("factorial(5) is: %lld. \n", factorial(5));
    printf("factorial(10) is: %lld. \n", factorial(10));
    printf("factorial(20) is: %lld. \n", factorial(20));
    printf("factorial(50) is: %lld. \n", factorial(50));
    printf("fibonacci(5) is: %lld. \n", fibonacci(5));
    printf("fibonacci(10) is: %lld. \n", fibonacci(10));
    printf("fibonacci(20) is: %lld. \n", fibonacci(20));
    printf("fibonacci(50) is: %lld. \n", fibonacci(50));
    int i = 314159, j = 271828;
    printf("gcd of %d and %d is: %d. \n", i, j, gcd(i, j));

    return 0;
}


