#include <stdio.h>
#include "cli/parser.h"

int main(int argc, char *argv[]) {
    Options options = parse(argc, argv);
    printf("%d %d %d %d %d %d", options.has_unrecognized, options.has_help, options.has_roots, options.has_iterations,
           options.has_test_root, options.has_test_integral);
}
