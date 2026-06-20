#ifndef CLI_ACTIONS_H
#define CLI_ACTIONS_H

#include <stdio.h>
#include "parser.h"

void print_help(FILE *out);
void print_root(FILE *out);
void print_iterations(FILE *out);
void print_area(FILE *out);
void test_root(FILE *out, const TestRootArgs *args);
void test_integral(FILE *out, const TestIntegralArgs *args);

#endif
