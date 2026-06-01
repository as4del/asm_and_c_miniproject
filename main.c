#include <stdio.h>
#include <math.h>
#include <string.h>
#include "integral.h"
#include "root.h"

// подключенные библиотеки из ассемблера
extern double f1(double);
extern double f2(double);
extern double f3(double);


// прототип функции
typedef double f_asm(double);


// функции для теста
extern void parabola_cub(double a, double b, double eps);
extern void parabola_line(double a, double b, double eps);
extern void line_cub(double a, double b, double eps);
extern void parabola_int(double a, double b, double eps);
extern void line_int(double a, double b, double eps);
extern void cub_int(double a, double b, double eps);


extern int count_iterations; // глобальный счетчик итераций
int help_cmd = 0; // флаг хелпа
int root_cmd = 0; // флаг вывода точек пересечения
int iter_cmd = 0; // флаг вывода итераций
int test_root_cmd = 0; // флаг теста поиска точек
int test_integ_cmd = 0; // флаг теста поиска интеграла






void start_test_root(char *str) {
    int fu1, fu2;
    double a, b, eps, r;
    sscanf(str, "%d:%d:%lf:%lf:%lf:%lf", &fu1, &fu2, &a, &b, &eps, &r);
    f_asm *first = NULL;
    f_asm *second = NULL;
    if (fu1 == 1) {
        first = f1;
    } else if (fu1 == 2) {
        first = f2;
    } else {
        first = f3;
    }

    if (fu2 == 1) {
        second = f1;
    } else if (fu2 == 2) {
        second = f2;
    } else {
        second = f3;
    }

    double ans = root(first, second, a, b, eps);
    double pogr = fabs(ans - r);
    double ot_pogr = pogr / r;
    if (count_iterations == 100) {
        printf("На этом отрезке функции не пересекаются или имеют более 1 точки пересечения\n");
    }
    printf("%lf %lf %lf\n", ans, pogr, ot_pogr);
}

// тест поиска интеграла
void start_test_integ(char *str) {
    int f;
    double a, b, eps, r;
    sscanf(str, "%d:%lf:%lf:%lf:%lf", &f, &a, &b, &eps, &r);

    f_asm *first = NULL;
    if (f == 1) {
        first = f1;
    } else if (f == 2) {
        first = f2;
    } else {
        first = f3;
    }

    double ans = integral(first, a, b, eps);
    double pogr = fabs(ans - r);
    double ot_pogr = pogr / r;
    printf("%lf %lf %lf\n", ans, pogr, ot_pogr);
}

// вычисление площади фигуры из условия
void start_main() {
    double t1 = root(f1, f3, 0.0, 3.0, 0.00001);
    if (iter_cmd == 1 || root_cmd == 1) {
        printf("Для y = e^(-x) + 3 и y = 1/x\n");
    }
    if (iter_cmd == 1) {
        printf("Количество итераций для поиска точки пересечения - %d\n", count_iterations);
    }
    if (root_cmd == 1) {
        printf("Точка пересечения - %lf\n", t1);
    }

    double t2 = root(f1, f2, 0.0, 3.0, 0.00001);
    if (iter_cmd == 1 || root_cmd == 1) {
        printf("Для y = e^(-x) + 3 и y = 2x - 2\n");
    }

    if (iter_cmd == 1) {
        printf("Количество итераций для поиска точки пересечения - %d\n", count_iterations);
    }
    if (root_cmd == 1) {
        printf("Точка пересечения - %lf\n", t2);
    }

    double t3 = root(f2, f3, 0.1, 3.0, 0.00001);
    if (iter_cmd == 1 || root_cmd == 1) {
        printf("Для y = 1/x и y = 2x - 2\n");
    }

    if (iter_cmd == 1) {
        printf("Количество итераций для поиска точки пересечения - %d\n", count_iterations);
    }
    if (root_cmd == 1) {
        printf("Точка пересечения - %lf\n", t3);
    }

    double r1 = integral(f1, t1, t2, 0.0001);
    double r2 = integral(f2, t3, t2, 0.0001);
    double r3 = integral(f3, t1, t3, 0.0001);

    double ans = r1 - r2 - r3;
    printf("Искомая площадь - %lf\n", ans);
}

int main(int argc, char** argv) {
    if (argc == 1) {
        start_main();
        return 0;
    }

    // считывания флагов
    for (int i = 1; i < argc; ++i) {
         if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
             help_cmd = 1;
         } else if (strcmp(argv[i], "--root") == 0 || strcmp(argv[i], "-r") == 0) {
             root_cmd = 1;
         } else if (strcmp(argv[i], "--iterations") == 0 || strcmp(argv[i], "-i") == 0) {
             iter_cmd = 1;
         }
    }

    if (help_cmd == 1) {
        printf("Опции --help и -h выводят на печать все допустимые ключ командной строки.\n");
        printf("\n");
        printf("Опции --root и -r печатают абсциссы точек пересечения кривых.\n");
        printf("\n");
        printf("Опции --iterations и -i печатают число итераций, потребовавшихся на приближенное решение уравнений при поиске точек пересечения.\n");
        printf("\n");
        printf("Опции --test-root и -R позволяют протестировать функцию"
"root. Фактические параметры вызова root задаются единственным параметром этой опции в виде F1:F2:A:B:E:R, где F1, F2 — номера используемых функций, A, B, E — значения параметров a, b, eps1 функции root,"
"R — правильный ответ (вычисленный аналитически).\n");
        printf("\n");
        printf("Опции --test-integral и -I позволяют протестировать функцию integral. Фактические параметры вызова integral задаются единственным параметром этой опции в виде F:A:B:E:R, где F — номера используемой функций, A, B, E — значения параметров a, b, eps2 функции"
"integral, R — правильный ответ (вычисленный аналитически).\n");
        printf("\n");
        printf("\n");
        return 0;
    }



    if (strcmp(argv[1], "--test-root") == 0 || strcmp(argv[1], "-R") == 0) {
        test_root_cmd = 1;
    } else if (strcmp(argv[1], "--test-integral") == 0 || strcmp(argv[1], "-I") == 0) {
        test_integ_cmd = 1;
    }

    if (test_root_cmd == 1) {
        start_test_root(argv[2]);
        return 0;
    }

    if (test_integ_cmd == 1) {
        start_test_integ(argv[2]);
        return 0;
    }

    start_main();
}
