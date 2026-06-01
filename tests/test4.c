#include "integral.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>

extern int count_iterations;

double parabola(double x) {return x * x;}
double line(double x) {return x;}
double cub(double x) {return x * x * x;}

int main() {
    double ans = integral(parabola, 3.0, 10.0, 0.001);
    assert(fabs(ans - 324.33) < 0.01);

    printf("root1_integral: OK\n");
}
