#include <math.h>
#include <stdio.h>
#include "calculus/integral.h"
#include "functions.h"
#include "tests.h"

typedef struct {
    double expected;
    double a;
    double b;
    double eps;

    afunc f;
} integral_testcase_t;

int test_integral(void) {
    const integral_testcase_t *tc;
    double I;
    double delta;
    int size;
    int errors;

    static const integral_testcase_t cases[] = {
        // simple
        {.expected = -0.1757, .a = 0.61906, .b = 1.51213, .eps = 0.0001, .f = f1},
        {.expected = 3.7500, .a = -1, .b = 0, .eps = 0.0001, .f = f2},
        {.expected = 1.6272, .a = 0.12003, .b = 1, .eps = 0.0001, .f = f3},
        {.expected = 36.4628, .a = -2, .b = 4, .eps = 0.0001, .f = f1},
        {.expected = -1900.0000, .a = -10, .b = 10, .eps = 0.0001, .f = f2},
        {.expected = 113.9441, .a = 0.1, .b = 12, .eps = 0.0001, .f = f3},

        // variable epsilon
        {.expected = 36.4, .a = -2, .b = 4, .eps = 0.1, .f = f1},
        {.expected = 36.46, .a = -2, .b = 4, .eps = 0.01, .f = f1},
        {.expected = 36.462, .a = -2, .b = 4, .eps = 0.001, .f = f1},
        {.expected = 36.462814750, .a = -2, .b = 4, .eps = 0.000000001, .f = f1},
        {.expected = 3.750000000, .a = -1, .b = 0, .eps = 0.000000001, .f = f2},

        // a = b
        {.expected = 0.0000, .a = 0.71206, .b = 0.712066, .eps = 0.0001, .f = f1},
        {.expected = 0.0000, .a = -2, .b = -2, .eps = 0.0001, .f = f2},
        {.expected = 0.0000, .a = 1.2, .b = 1.2, .eps = 0.0001, .f = f3},

        // a > b
        {.expected = 0.1757, .a = 1.51213, .b = 0.61906, .eps = 0.0001, .f = f1},
        {.expected = -3.7500, .a = 0, .b = -1, .eps = 0.0001, .f = f2},
        {.expected = -1.6272, .a = 1, .b = 0.12003, .eps = 0.0001, .f = f3},
        {.expected = -24.0126, .a = 4, .b = 3, .eps = 0.0001, .f = f1},
        {.expected = -2.2500, .a = 1, .b = -2, .eps = 0.0001, .f = f2},
        {.expected = -5.2723, .a = 2, .b = 0.4003, .eps = 0.0001, .f = f3},
    };

    size = sizeof(cases) / sizeof(cases[0]);
    errors = 0;

    for (int i = 0; i < size; ++i) {
        tc = &cases[i];
        I = integral(tc->f, tc->a, tc->b, tc->eps);
        delta = fabs(I - tc->expected);

        if (delta > tc->eps) {
            printf("[FAIL] Test %d\n"
                   "       Expected: %.9lf\n"
                   "       Actual:   %.9lf\n"
                   "       Delta:    %e > %e\n"
                   "       Source:   %s\n",
                   i + 1, tc->expected, I, delta, tc->eps, __FILE__);
            ++errors;
        }
    }

    printf("=== Integral tests: %d/%d passed ===\n\n", size - errors, size);

    return errors;
}
