#include "tests.h"

int main(int argc, char *argv[]) {
    int errors = 0;

    errors += test_root();
    errors += test_integral();

    return (errors == 0) ? 0 : 1;
}
