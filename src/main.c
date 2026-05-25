#include <stdio.h>
#include <getopt.h>
#include "functions.h"
#include "calculus/root.h"
#include "calculus/integral.h"

int main(int argc, char* argv[])
{
    const char *short_options = "hriRI";

    const struct option long_options[] = {
        {"help",          no_argument, NULL, 'h'},
        {"root",          no_argument, NULL, 'r'},
        {"iterations",    no_argument, NULL, 'i'},
        {"test-root",     no_argument, NULL, 'R'},
        {"test-integral", no_argument, NULL, 'I'},
        {NULL,            0,           NULL, 0}
    };

    int option;

    while ((option = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
    {
        switch (option)
        {
        case 'h':
            break;
        case 'r':
            RootResult res = root(f1, f2, df1, df2, -2.0, -0.1, 0.000001);
            printf("%lf", res.x);
            break;
        case 'i':
            break;
        case 'R':
            break;
        case 'I':
            break;
        default:
            break;
        }
    }

    // printf("%lf", integral(f1, -10.0, -0.1, 0.000001));

    return 0;
}
