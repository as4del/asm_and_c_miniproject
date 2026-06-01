#include "integral.h"
#include <math.h>

double integral(f_asm *f, double a, double b, double eps2) {
    int cur_n = 4;
    int cnt_iter = 0;
    double last_int = 0;
    while (1) {
        double h = (b - a) / cur_n;
        double integ = 0;
        for (int i = 1; i <= cur_n - 1; ++i) {
            integ += f(a + i * h);
        }
        integ += 0.5 * f(a + 0 * h);
        integ += 0.5 * f(a + cur_n * h);
        integ *= h;
        if (cnt_iter >= 1) {
            if (fabs(integ - last_int) / 3.0 < eps2) {
                return integ;
            }
        }
        cnt_iter++;
        last_int = integ;
        cur_n *= 2;
    }
}