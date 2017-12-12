#include <stdio.h>
#include <mysort/types.h>
#include <mysort/usage.h>
#include <mysort/args.h>
#include <mysort/die.h>

int main(int argc, char **argv)
{
    string_t *data_buf = NULL;
    parse_args(argc, argv);
    if (opts.invalid_flag)
    {
        show_usage_and_exit(1);
    }

    printf("Program name: %s\n", opts.program_name);
}
