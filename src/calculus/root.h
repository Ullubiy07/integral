#ifndef CALCULUS_ROOT_H
#define CALCULUS_ROOT_H

typedef double (*afunc)(double);

typedef enum {
    ROOT_OK,
    ROOT_BAD_ARGS,
    ROOT_NOT_FOUND,
    ROOT_MAX_ITERATIONS,
    ROOT_MATH_ERROR,
} RootStatus;

typedef struct {
    double x;
    int iterations;
} RootResult;

RootStatus root(afunc f, afunc g, afunc df, afunc dg, double a, double b, double eps, RootResult *res);

const char *get_root_status(RootStatus status);

#endif
