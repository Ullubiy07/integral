#include <math.h>
#include <stdlib.h>
#include "options.h"
#include "calculus/integral.h"
#include "calculus/root.h"
#include "functions.h"

typedef struct {
    afunc f;
    afunc df;
} FuncPair;

static const double eps = 0.0000001;

static const FuncPair funcArr[] = {{f1, df1}, {f2, df2}, {f3, df3}};

static void get_funcs(int f_idx, afunc *f, afunc *df) {
    if (f_idx <= 0 || sizeof(funcArr) / sizeof(funcArr[0]) < f_idx) {
        return;
    }
    FuncPair pair = funcArr[f_idx - 1];
    if (f != NULL) {
        *f = pair.f;
    }
    if (df != NULL) {
        *df = pair.df;
    }
}

#define CHECK_ROOT(status_expr)                                            \
    do {                                                                   \
        RootStatus status_ = status_expr;                                  \
        if (status_ != ROOT_OK) {                                          \
            fprintf(stderr,                                                \
                    "%s: %s\n"                                             \
                    "Try '%s --help' for more information.\n",             \
                    program_name, get_root_status(status_), program_name); \
            exit(1);                                                       \
        }                                                                  \
    } while (0)

#define CHECK_INTEGRAL(status_expr)                                            \
    do {                                                                       \
        IntegralStatus status_ = status_expr;                                  \
        if (status_ != INTEGRAL_OK) {                                          \
            fprintf(stderr,                                                    \
                    "%s: %s\n"                                                 \
                    "Try '%s --help' for more information.\n",                 \
                    program_name, get_integral_status(status_), program_name); \
            exit(1);                                                           \
        }                                                                      \
    } while (0)

void print_help(FILE *out) {
    static const char *help_msg =
        "Usage: %s [OPTION]...\n"
        "Compute the area of a plane figure bounded by three predefined curves\n\n"
        "Options:\n"
        "  -h, --help                 print valid command line options\n"
        "  -r, --root                 print x-coordinates of curve intersections\n"
        "  -i, --iterations           print number of iterations required to solve equations\n"
        "                             when searching for intersection points\n\n"
        "  -R, --test-root=ARGS       test root function with format F1:F2:A:B:E:R, where:\n"
        "                             F1, F2 - function indices (1-3),\n"
        "                             A, B - search interval boundaries,\n"
        "                             E - precision, R - expected root value\n\n"
        "  -I, --test-integral=ARGS   test integral function with format F:A:B:E:R, where:\n"
        "                             F - function index (1-3),\n"
        "                             A, B - integration interval boundaries,\n"
        "                             E - precision, R - expected integral value\n";
    fprintf(out, help_msg, program_name);
}

void print_root(FILE *out) {
    RootResult res12, res13, res23_1, res23_2;

    CHECK_ROOT(root(f1, f2, df1, df2, -2.0, -0.1, eps, &res12));
    CHECK_ROOT(root(f1, f3, df1, df3, -6.0, 2, eps, &res13));
    CHECK_ROOT(root(f2, f3, df2, df3, -4.0, -0.2, eps, &res23_1));
    CHECK_ROOT(root(f2, f3, df2, df3, 0.2, 4, eps, &res23_2));

    fprintf(out, "Roots: %lf %lf %lf %lf\n", res12.x, res13.x, res23_1.x, res23_2.x);
}

void print_iterations(FILE *out) {
    RootResult res12, res13, res23_1, res23_2;

    CHECK_ROOT(root(f1, f2, df1, df2, -2.0, -0.1, eps, &res12));
    CHECK_ROOT(root(f1, f3, df1, df3, -6.0, 2, eps, &res13));
    CHECK_ROOT(root(f2, f3, df2, df3, -4.0, -0.2, eps, &res23_1));
    CHECK_ROOT(root(f2, f3, df2, df3, 0.2, 4, eps, &res23_2));

    fprintf(out, "Iterations: %d %d %d %d\n", res12.iterations, res13.iterations, res23_1.iterations,
            res23_2.iterations);
}

void print_area(FILE *out) {
    RootResult res12, res13, res23;
    double I1, I2, I3;

    CHECK_ROOT(root(f1, f2, df1, df2, -2.0, -0.1, eps, &res12));
    CHECK_ROOT(root(f1, f3, df1, df3, -6.0, 2, eps, &res13));
    CHECK_ROOT(root(f2, f3, df2, df3, -4.0, -0.2, eps, &res23));

    CHECK_INTEGRAL(integral(f1, res13.x, res12.x, eps, &I1));
    CHECK_INTEGRAL(integral(f2, res23.x, res12.x, eps, &I2));
    CHECK_INTEGRAL(integral(f3, res13.x, res23.x, eps, &I3));

    fprintf(out, "Area: %lf\n", I1 - I2 - I3);
}

void test_root(FILE *out, const TestRootArgs *args) {
    RootResult res;
    afunc f1, f2, df1, df2;
    double abs_err, rel_err;

    get_funcs(args->f1_idx, &f1, &df1);
    get_funcs(args->f2_idx, &f2, &df2);

    CHECK_ROOT(root(f1, f2, df1, df2, args->a, args->b, args->eps, &res));

    abs_err = fabs(res.x - args->expected);
    rel_err = abs_err / fabs(args->expected);

    fprintf(out, "%lf %lf %lf\n", res.x, abs_err, rel_err);
}

void test_integral(FILE *out, const TestIntegralArgs *args) {
    afunc f;
    double I, abs_err, rel_err;

    get_funcs(args->f_idx, &f, NULL);

    CHECK_INTEGRAL(integral(f, args->a, args->b, args->eps, &I));

    abs_err = fabs(I - args->expected);
    rel_err = abs_err / fabs(args->expected);

    fprintf(out, "%lf %lf %lf\n", I, abs_err, rel_err);
}
