#ifndef CALCULUS_INTEGRAL_H
#define CALCULUS_INTEGRAL_H

typedef double (*afunc)(double);

double integral(afunc f, double a, double b, double eps);

#endif
