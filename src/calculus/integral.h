#ifndef CALCULUS_INTEGRAL_H
#define CALCULUS_INTEGRAL_H

typedef double (*afunc)(double);

typedef enum {
    INTEGRAL_OK,
    INTEGRAL_BAD_ARGS,
    INTEGRAL_MAX_PARTITION,
    INTEGRAL_MATH_ERROR,
} IntegralStatus;

IntegralStatus integral(afunc f, double a, double b, double eps, double *res);

const char *get_integral_status(IntegralStatus status);

#endif
