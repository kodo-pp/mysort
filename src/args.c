#include <mysort/args.h>
#include <mysort/types.h>
#include <mysort/die.h>
#include <mysort/usage.h>
#include <string.h>


options_t opts;

void parse_args(int argc, char **argv)
{
    if (argc <= 0)
    {
        die("Internal error: argc <= 0");
    }

    // args - глобальная структура
    opts.program_name = argv[0];

    for (int i = 1; i < argc; ++i)
    {
        if (! strcmp(argv[i], "--help"))
        {
            show_usage_and_exit(0);
        }
        else if (! strcmp(argv[i], "-n"))
        {
            opts.sort_comparison = SC_NUMERIC;
        }
    }
}
