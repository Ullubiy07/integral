#include <math.h>
#include "root.h"

typedef enum
{
    NEGATIVE = -1,
    ZERO     = 0,
    POSITIVE = 1
} Sign;

static double F(afunc f, afunc g, double x)
{
    return f(x) - g(x);
}

static Sign sign(double x)
{
    const int eps = 1e-6;
    if (fabs(x) < eps)
        return ZERO;
    if (x < 0)
        return NEGATIVE;
    return POSITIVE;
}

RootResult root(afunc f, afunc g, afunc df, afunc dg, double a, double b, double eps)
{
    double x;
    double x_prev;
    int iterations = 0;

    // F'(x) * F''(x) > 0
    if (sign((F(f, g, a) + F(f, g, b)) / 2 - F(f, g, (a + b) / 2)) * 
        sign(F(f, g, b) - F(f, g, a)) == POSITIVE)
        x = b;
    else
        x = a;

    do {
        x_prev = x;
        x = x_prev - F(f, g, x_prev) / F(df, dg, x_prev);
        iterations++;
    } while (fabs(x - x_prev) >= eps);

    return (RootResult) { .x = x, .iterations = iterations };
}
