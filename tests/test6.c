#include "integral.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>

extern int count_iterations;

double parabola(double x) {return x * x;}
double line(double x) {return x;}
double cub(double x) {return x * x * x;}

int main() {
    double ans = integral(cub, 3.0, 10.0, 0.001);
    assert(fabs(ans - 2479.75) < 0.01);
    printf("test3_integral: OK\n");
}
