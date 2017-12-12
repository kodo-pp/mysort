#include <stdio.h>
#include <mysort/usage.h>
#include <mysort/types.h>

NORETURN void show_usage_and_exit(int exit_code = 1)
{
    printf("Usage: %s [--help] [FILENAME]\n", opts.program_name);
    exit(exit_code);
}
