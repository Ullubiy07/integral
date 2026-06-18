#include <math.h>
#include <stddef.h>
#include "root.h"

typedef enum { MINUS = -1, ZERO = 0, PLUS = 1 } Sign;
enum { ITERATIONS_LIMIT = 1000 };

static double F(afunc f, afunc g, double x) { return f(x) - g(x); }

static Sign sign(double x) {
    if (fabs(x) < 1e-12) {
        return ZERO;
    }
    if (x < 0) {
        return MINUS;
    }
    return PLUS;
}

RootStatus root(afunc f, afunc g, afunc df, afunc dg, double a, double b, double eps, RootResult *res) {
    if (res == NULL || f == NULL || g == NULL || df == NULL || dg == NULL || eps <= 0.0 || a > b) {
        return ROOT_BAD_ARGS;
    }

    double x, x_prev, dF;
    double fa = F(f, g, a);
    double fb = F(f, g, b);
    int iterations = 0;

    Sign d1f_sign = sign(fb - fa);
    Sign d2f_sign = sign((fa + fb) / 2 - F(f, g, (a + b) / 2));

    // F'(x) * F''(x) > 0
    if (d1f_sign * d2f_sign == PLUS) {
        x = b;
    } else {
        x = a;
    }

    do {
        if (iterations >= ITERATIONS_LIMIT) {
            return ROOT_MAX_ITERATIONS;
        }

        x_prev = x;
        dF = F(df, dg, x_prev);

        if (sign(dF) == ZERO) {
            return ROOT_MATH_ERROR;
        }
        x = x_prev - F(f, g, x_prev) / dF;

        if (!isfinite(x)) {
            return ROOT_MATH_ERROR;
        }

        iterations++;
    } while (fabs(x - x_prev) >= eps);

    // x ∉ [a, b]
    if (x < a - eps || x > b + eps) {
        return ROOT_NOT_FOUND;
    }

    res->x = x;
    res->iterations = iterations;

    return ROOT_OK;
}

const char *get_root_status(RootStatus status) {
    switch (status) {
    case ROOT_OK:
        return "OK";
    case ROOT_BAD_ARGS:
        return "BAD_ARGS";
    case ROOT_NOT_FOUND:
        return "NOT_FOUND";
    case ROOT_MAX_ITERATIONS:
        return "MAX_ITERATIONS";
    case ROOT_MATH_ERROR:
        return "MATH_ERROR";
    default:
        return "UNKNOWN";
    }
}
