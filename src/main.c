#include <stdio.h>
#include <mysort/types.h>
#include <mysort/usage.h>
#include <mysort/args.h>

int main(int argc, char **argv)
{
    string_t *data_buf = NULL;
    parse_args(argc, argv);
    if (opts.invalid_flag)
    {
        show_usage_and_exit();
    }
}
