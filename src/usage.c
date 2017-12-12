#include <stdio.h>
#include <stdlib.h>
#include <mysort/usage.h>
#include <mysort/types.h>
#include <mysort/args.h>

NORETURN void show_usage_and_exit(int exit_code)
{
    printf("Usage: %s [--help] [FILENAME]\n", opts.program_name);
    exit(exit_code);
}
