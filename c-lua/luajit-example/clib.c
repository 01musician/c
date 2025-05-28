// clib.c
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

int add(int a, int b) {
    return a + b;
}

void print_point(Point p) {
    printf("Point: (%d, %d)\n", p.x, p.y);
}

