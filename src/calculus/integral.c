#include <math.h>
#include <stddef.h>
#include "integral.h"

// 2 * INIT_PARTITION <= MIN_PARTITION <= MAX_PARTITION
enum { RUNGE_DIVISOR = 3, INIT_PARTITION = 1 << 4, MIN_PARTITION = 1 << 14, MAX_PARTITION = 1 << 20 };

static double calc_init_sum(afunc f, double a, double b, int n0) {
    double h = (b - a) / n0;
    double sum = 0.5 * (f(a) + f(b));

    for (int i = 1; i < n0; i++) {
        sum += f(a + i * h);
    }

    return sum;
}

static double calc_next_sum(afunc f, double a, double b, int n, double prev_sum) {
    double h = (b - a) / (2 * n);
    double sum = prev_sum;

    for (int i = 1; i < 2 * n; i += 2) {
        sum += f(a + i * h);
    }

    return sum;
}

double integral(afunc f, double a, double b, double eps) {
    if (f == NULL || eps <= 0.0) {
        return 0.0;
    }

    double I_old, I_new;
    int n = INIT_PARTITION;
    double h = (b - a) / n;
    double sum = calc_init_sum(f, a, b, n);

    I_new = sum * h;

    do {
        I_old = I_new;
        sum = calc_next_sum(f, a, b, n, sum);

        h /= 2;
        n *= 2;

        I_new = sum * h;
    } while ((fabs(I_new - I_old) / RUNGE_DIVISOR >= eps || n < MIN_PARTITION) && (2 * n) <= MAX_PARTITION);

    return I_new;
}
