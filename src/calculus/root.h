#ifndef CALCULUS_ROOT_H
#define CALCULUS_ROOT_H

typedef double (*afunc)(double);

typedef struct {
    double x;
    int iterations;
} RootResult;

RootResult root(afunc f, afunc g, afunc df, afunc dg, double a, double b, double eps);

#endif
