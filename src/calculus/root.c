#include <math.h>
#include <stddef.h>
#include "root.h"

typedef enum { NEGATIVE = -1, ZERO = 0, POSITIVE = 1 } Sign;
enum { MAX_ITERATIONS = 1000 };

static double F(afunc f, afunc g, double x) { return f(x) - g(x); }

static Sign sign(double x) {
    const double eps = 1e-6;
    if (fabs(x) < eps) {
        return ZERO;
    }
    if (x < 0) {
        return NEGATIVE;
    }
    return POSITIVE;
}

RootResult root(afunc f, afunc g, afunc df, afunc dg, double a, double b, double eps) {
    if (f == NULL || g == NULL || df == NULL || dg == NULL || eps <= 0.0 || a > b) {
        return (RootResult){0};
    }

    double x, x_prev, dF;
    int iterations = 0;

    int d1f_sign = sign(F(f, g, b) - F(f, g, a));
    int d2f_sign = sign((F(f, g, a) + F(f, g, b)) / 2 - F(f, g, (a + b) / 2));

    // F'(x) * F''(x) > 0
    if (d1f_sign * d2f_sign == POSITIVE) {
        x = b;
    } else {
        x = a;
    }

    do {
        x_prev = x;
        dF = F(df, dg, x_prev);

        if (sign(dF) == ZERO) {
            break;
        }

        x = x_prev - F(f, g, x_prev) / dF;
        iterations++;
    } while (fabs(x - x_prev) >= eps && iterations < MAX_ITERATIONS);

    return (RootResult){.x = x, .iterations = iterations};
}
