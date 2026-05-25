#include <math.h>
#include "integral.h"

enum
{
    INITIAL_PARTITION_COUNT = 10,
    RUNGE_DIVISOR = 3
};

static double calc_init_sum(afunc f, double a, double b, int n0)
{
    double h = (b - a) / n0;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n0; i++)
        sum += f(a + i * h);

    return sum;
}

static double calc_next_sum(afunc f, double a, double b, int n, double prev_sum)
{
    double h = (b - a) / (2 * n);
    double sum = prev_sum;

    for (int i = 1; i < 2 * n; i += 2)
        sum += f(a + i * h);

    return sum;
}

double integral(afunc f, double a, double b, double eps)
{
    int n = INITIAL_PARTITION_COUNT;
    double h = (b - a) / n;
    double sum = calc_init_sum(f, a, b, n);
    double I_old, I_new;

    I_new = sum * h;
    
    do {
        I_old = I_new;
        sum = calc_next_sum(f, a, b, n, sum);

        h /= 2;
        n *= 2;

        I_new = sum * h;
    } while (fabs(I_new - I_old) / RUNGE_DIVISOR >= eps);
    
    return I_new;
}
