#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "parser.h"

static TestRootArgs parse_test_root_args(const char *args) {
    TestRootArgs res;

    if (sscanf(args, "%d:%d:%lf:%lf:%lf:%lf", &res.f1_idx, &res.f2_idx, &res.a, &res.b, &res.eps, &res.expected) != 6) {
        fprintf(stderr,
                "%s: invalid argument '%s' for '--test-root'\n"
                "Expected argument format: F1:F2:A:B:E:R\n"
                "Try '%s --help' for more information.\n",
                program_name, args, program_name);
        exit(1);
    }
    return res;
}

static TestIntegralArgs parse_test_integral_args(const char *args) {
    TestIntegralArgs res;

    if (sscanf(args, "%d:%lf:%lf:%lf:%lf", &res.f_idx, &res.a, &res.b, &res.eps, &res.expected) != 5) {
        fprintf(stderr,
                "%s: invalid argument '%s' for '--test-integral'\n"
                "Expected argument format: F:A:B:E:R\n"
                "Try '%s --help' for more information.\n",
                program_name, args, program_name);
        exit(1);
    }
    return res;
}

Options parse(int argc, char *argv[]) {
    static const char *short_options = "hriRI";

    static const struct option long_options[] = {{"help", no_argument, NULL, 'h'},
                                                 {"root", no_argument, NULL, 'r'},
                                                 {"iterations", no_argument, NULL, 'i'},
                                                 {"test-root", required_argument, NULL, 'R'},
                                                 {"test-integral", required_argument, NULL, 'I'},
                                                 {NULL, 0, NULL, 0}};

    Options options = {0};

    int opt;
    while ((opt = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (opt) {
        case 'h':
            options.has_help = 1;
            break;
        case 'r':
            options.has_root = 1;
            break;
        case 'i':
            options.has_iterations = 1;
            break;
        case 'R':
            options.has_test_root = 1;
            options.test_root_args = parse_test_root_args(optarg);
            break;
        case 'I':
            options.has_test_integral = 1;
            options.test_integral_args = parse_test_integral_args(optarg);
            break;
        case '?':
            fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
            exit(2);
            break;
        default:
            fprintf(stderr, "%s: internal error", argv[0]);
            exit(2);
        }
    }

    if (argc == 1) {
        options.empty = 1;
    }

    return options;
}
