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
    unsigned int has_help : 1;
    unsigned int has_root : 1;
    unsigned int has_iterations : 1;
    unsigned int has_test_root : 1;
    unsigned int has_test_integral : 1;
    unsigned int empty : 1;
} Options;

Options parse(int argc, char *argv[]);

#endif
