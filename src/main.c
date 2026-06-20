#include <stdio.h>
#include "cli/handler.h"
#include "cli/parser.h"

int main(int argc, char *argv[]) {
    Options options = parse(argc, argv);
    handle_command(stdout, &options);
    return 0;
}
