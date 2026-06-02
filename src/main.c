#include <stdio.h>
#include "cli/handler.h"
#include "cli/parser.h"

const char *program_name = NULL;

int main(int argc, char *argv[]) {
    program_name = argv[0];
    Options options = parse(argc, argv);
    handle_command(stdout, &options);
    return 0;
}
