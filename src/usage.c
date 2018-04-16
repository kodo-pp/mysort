#include <stdio.h>
#include <stdlib.h>
#include <mysort/usage.h>
#include <mysort/types.h>
#include <mysort/args.h>

NORETURN void show_usage_and_exit(int exit_code) {
    fprintf(stderr, "Usage: %s [OPTIONS] [FILENAME [FILENAME ...]]\n", opts.program_name);
    fprintf(stderr, "OPTIONS:\n");
    fprintf(stderr, "    -r | --reverse              Reverse sort\n");
    fprintf(stderr, "    -n | --numeric-sort         Sort numbers naturally\n");
    fprintf(stderr, "    -R | --random-sort          Shuffle input lines\n");
    fprintf(stderr, "    -h | --human-numeric-sort   Naturally sort suffixed numbers like 100K = 100000, 27M = 27000000\n");
    fprintf(stderr, "         --immediate-sort       Sort data just as we read it.\n");
    fprintf(stderr, "                                    WARNING: this option (--immediate-sort) can only be used when reading from stdin\n");
    fprintf(stderr, "    -v | --version              Show version information and exit\n");
    fprintf(stderr, "         --help                 Show usage information and exit\n");
    fprintf(stderr, "    -o FILE                     Write output to FILE instead of stdout\n");
    exit(exit_code);
}
