#include <stdio.h>
#include <stdlib.h>
#include <mysort/usage.h>
#include <mysort/types.h>
#include <mysort/args.h>

NORETURN void show_usage_and_exit(int exit_code) {
    fprintf(stderr, "Usage: %s [-r] [--reverse] [--help] [FILENAME]\n", opts.program_name);
    fprintf(stderr, "    -r | --reverse    Reverse sort\n");
    fprintf(stderr, "         --help       Show usage information and exit\n");
    exit(exit_code);
}
