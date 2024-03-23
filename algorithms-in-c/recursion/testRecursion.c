#include<stdlib.h>
#include<stdio.h>
#include "factorial.h"

int main(int argc, char **argv)
{
    printf("factorial(5) is: %lld. \n", factorial(5));
    printf("factorial(10) is: %lld. \n", factorial(10));
    printf("factorial(20) is: %lld. \n", factorial(20));
    printf("factorial(50) is: %lld. \n", factorial(50));

    return 0;
}


