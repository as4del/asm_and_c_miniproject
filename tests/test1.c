#include "root.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>

extern int count_iterations;

double parabola(double x) {return x * x;}
double line(double x) {return x;}
double cub(double x) {return x * x * x;}
int main() {
    double ans = root(parabola, cub, 0.5, 10.0, 0.0001);


    if (count_iterations == 100) {
        printf("test1_root: ");
        printf("На этом отрезке функции не пересекаются или имеют более 1 точки пересечения\n");
        return 0;
    }

    assert(fabs(ans - 1.0) < 0.0001 || fabs(ans - 0.0) < 0.0001);
    printf("test1_root : OK\n");
}
