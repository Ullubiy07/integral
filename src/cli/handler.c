#include "options.h"
#include "handler.h"

void handle_command(FILE *out, const Options *options) {
    if (options->has_help) {
        print_help(out);
        return;
    }
    if (options->empty) {
        print_area(out);
        return;
    }

    if (options->has_root) {
        print_root(out);
    }
    if (options->has_iterations) {
        print_iterations(out);
    }
    if (options->has_test_root) {
        test_root(out, &options->test_root_args);
    }
    if (options->has_test_integral) {
        test_integral(out, &options->test_integral_args);
    }
}
