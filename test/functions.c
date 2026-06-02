#include <math.h>
#include "functions.h"

double f1(double x) { return exp(x) - 3 * x; }

double f2(double x) { return pow(x, 3) - 3 * pow(x, 2) + 5; }

double f3(double x) { return log(x) + x + 2; }

double df1(double x) { return exp(x) - 3; }

double df2(double x) { return 3 * pow(x, 2) - 6 * x; }

double df3(double x) { return 1 / x + 1; }
