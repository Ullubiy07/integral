#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <stdbool.h>

typedef struct {
    double a;
    double b;
    double eps;
    double expected;
    int f1_idx;
    int f2_idx;
} TestRootArgs;

typedef struct {
    double a;
    double b;
    double eps;
    double expected;
    int f_idx;
} TestIntegralArgs;

typedef struct {
    TestRootArgs test_root_args;
    TestIntegralArgs test_integral_args;

    bool has_help;
    bool has_root;
    bool has_iterations;
    bool has_test_root;
    bool has_test_integral;
    bool empty;
} Options;

Options parse(int argc, char *argv[]);

#endif
