#ifndef CLI_PARSER_H
#define CLI_PARSER_H

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
    TestRootArgs test_root;
    TestIntegralArgs test_integral;
    int has_help;
    int has_roots;
    int has_iterations;
    int has_test_root;
    int has_test_integral;
    int has_unrecognized;
    int has_no_options;
} Options;

Options parse(int argc, char *argv[]);

#endif
