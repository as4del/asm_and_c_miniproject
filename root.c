#include "root.h"

int count_iterations = 0;


double root(f_asm *f, f_asm *g, double a, double b, double eps1) {
    count_iterations = 0;
    while (b - a >= eps1) {
        count_iterations++;
        if (count_iterations == 100) {
            return 0;
        }
        double mid = (a + b) / 2;
        double first = (f(a) - g(a)) * (f(mid) - g(mid));
        double second = (f(mid) - g(mid)) * (f(b) - g(b));
        if (first <= 0) {
            b = mid;
        } else if (second <= 0) {
            a = mid;
        } else {
            count_iterations = 100;
            return 0;
        }
    }
    return a;
}