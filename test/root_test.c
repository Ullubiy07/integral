#include <math.h>
#include <stdio.h>
#include "calculus/root.h"
#include "functions.h"
#include "tests.h"

typedef struct {
    double expected;
    double a;
    double b;
    double eps;

    afunc f;
    afunc g;
    afunc df;
    afunc dg;
} RootTestcase;

int test_root(void) {
    const RootTestcase *tc;
    RootStatus status;
    RootResult res;
    double delta;
    int size;
    int errors;

    static const RootTestcase cases[] = {
        // simple
        {.expected = -0.7690, .a = -2, .b = -0.5, .eps = 0.0001, .f = f1, .g = f2, .df = df1, .dg = df2},
        {.expected = 1.9101, .a = 1, .b = 3, .eps = 0.0001, .f = f1, .g = f2, .df = df1, .dg = df2},
        {.expected = 0.2039, .a = 0.1, .b = 0.5, .eps = 0.0001, .f = f1, .g = f3, .df = df1, .dg = df3},
        {.expected = 1.0000, .a = 0.5, .b = 1.5, .eps = 0.0001, .f = f2, .g = f3, .df = df2, .dg = df3},
        {.expected = 2.5879, .a = 2, .b = 3, .eps = 0.0001, .f = f1, .g = f3, .df = df1, .dg = df3},
        {.expected = 3.1297, .a = 3, .b = 4, .eps = 0.0001, .f = f2, .g = f3, .df = df2, .dg = df3},

        // variable epsilon
        {.expected = 3.1, .a = 3, .b = 4, .eps = 0.1, .f = f2, .g = f3, .df = df2, .dg = df3},
        {.expected = 3.12, .a = 3, .b = 4, .eps = 0.01, .f = f2, .g = f3, .df = df2, .dg = df3},
        {.expected = 3.129, .a = 3, .b = 4, .eps = 0.001, .f = f2, .g = f3, .df = df2, .dg = df3},
        {.expected = 3.129723988, .a = 3, .b = 4, .eps = 0.000000001, .f = f2, .g = f3, .df = df2, .dg = df3},
        {.expected = 2.587971589, .a = 2, .b = 3, .eps = 0.000000001, .f = f1, .g = f3, .df = df1, .dg = df3},

        // root = a = b
        {.expected = -0.7690, .a = -0.7690, .b = -0.7690, .eps = 0.0001, .f = f1, .g = f2, .df = df1, .dg = df2},
        {.expected = 1.9101, .a = 1.9101, .b = 1.9101, .eps = 0.0001, .f = f1, .g = f2, .df = df1, .dg = df2},
        {.expected = 0.2039, .a = 0.2039, .b = 0.2039, .eps = 0.0001, .f = f1, .g = f3, .df = df1, .dg = df3},
        {.expected = 1.0000, .a = 1.0000, .b = 1.0000, .eps = 0.0001, .f = f2, .g = f3, .df = df2, .dg = df3},
        {.expected = 2.5879, .a = 2.5879, .b = 2.5879, .eps = 0.0001, .f = f1, .g = f3, .df = df1, .dg = df3},
        {.expected = 3.1297, .a = 3.1297, .b = 3.1297, .eps = 0.0001, .f = f2, .g = f3, .df = df2, .dg = df3},
    };

    size = sizeof(cases) / sizeof(cases[0]);
    errors = 0;

    for (int i = 0; i < size; ++i) {
        tc = &cases[i];
        status = root(tc->f, tc->g, tc->df, tc->dg, tc->a, tc->b, tc->eps, &res);
        delta = fabs(res.x - tc->expected);

        if (status != ROOT_OK) {
            printf("[FAIL] Test %d: %s\n", i + 1, get_root_status(status));
            ++errors;
        } else if (delta > tc->eps) {
            printf("[FAIL] Test %d\n"
                   "       Expected: %.9lf\n"
                   "       Actual:   %.9lf\n"
                   "       Delta:    %e > %e\n",
                   i + 1, tc->expected, res.x, delta, tc->eps);
            ++errors;
        }
    }

    printf("=== Root tests: %d/%d passed ===\n\n", size - errors, size);

    return errors;
}
