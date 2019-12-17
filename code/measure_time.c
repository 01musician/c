#include<time.h>
#include<stdio.h>

int main()
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    printf("hello world.\n");

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("printf used: %f second to output hello wolrd\n", cpu_time_used);

    return 0;
}

