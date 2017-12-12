#include <stdio.h>
#include <mysort/types.h>
#include <mysort/usage.h>
#include <mysort/args.h>
#include <mysort/die.h>
#include <stdlib.h>
#include <mysort/config.h>
#include <mysort/sort.h>

int main(int argc, char **argv)
{
    string_t *data_buf = NULL;
    parse_args(argc, argv);
    if (opts.invalid_flag)
    {
        show_usage_and_exit(1);
    }

    switch (opts.output_type)
    {
        case OT_USAGE:
            show_usage_and_exit(2);
            break;
        case OT_VERSION:
            fprintf(stderr, "mysort v %s\n", VERSION_STRING);
            exit(2);
            break;
        case OT_SORT:
            sort_process();
            break;
        default:
            printf("?????? %d\n", opts.output_type);
            break;
    }

    /*printf("Program name: %s\n", opts.program_name);
    if (opts.input_file == NULL)
    {
        opts.input_file = "<NULL>";
    }
    printf("IT: %d, OT: %d, IF: %s, SC: %d\n", opts.input_type, opts.output_type, opts.input_file, opts.sort_comparison);*/

}
