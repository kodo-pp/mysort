#include <mysort/args.h>
#include <mysort/types.h>
#include <mysort/die.h>
#include <mysort/usage.h>
#include <mysort/config.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

options_t opts;

static bool treat_all_as_files = false;

const int OPTTP_FILE = 1;
const int OPTTP_OPT = 2;
const int OPTTP_SKIP = 3;
const int OPTTP_UNK = 0;

static int get_opt(string_t opt, const char *pattern) {
    if (treat_all_as_files) {
        return OPTTP_FILE;
    }
    if (strcmp(opt, "--") == 0) {
        treat_all_as_files = true;
        return OPTTP_SKIP;
    }
    if (strcmp(opt, pattern) == 0) {
        return OPTTP_OPT;
    } else {
        return OPTTP_UNK;
    }
}

void add_file(string_t filename) {
    static int input_files_count = 0;
    if (input_files_count + 1 > MAX_INPUT_FILES) {
        die("too many input files");
    }
    opts.input_files[input_files_count] = filename;
    opts.input_files[input_files_count + 1] = NULL;
    ++input_files_count;
}

void parse_args(int argc, char **argv) {
    if (argc <= 0) {
        die("Internal error: main: argc <= 0");
    }

    // opts - глобальная структура
    opts.program_name = argv[0];
    opts.sort_comparison = SC_NORMAL;
    opts.input_type = IT_STDIN;
    opts.output_type = OT_SORT;
    opts.strict = true;
    memset(opts.input_files, 0, sizeof(opts.input_files));

    /* string_t infile = NULL;*/

    /* int input_files_count = 0; */

    for (int i = 1; i < argc; ++i) {
        bool any_opt = false;
        //bool // any_known = false;
        int result;
        result = get_opt(argv[i], "--help");
        if (result != OPTTP_UNK) {
            any_opt = true;
        }
        if (result == OPTTP_SKIP) {
            // any_known = true;
            continue;
        }
        if (result == OPTTP_FILE) {
            // any_known = true;
            opts.input_type = IT_FILE;
            /* infile = argv[i]; */ add_file(argv[i]);
            continue;
        }
        if (result == OPTTP_OPT) {
            // any_known = true;
            opts.output_type = OT_USAGE;
            continue;
        }

        result = get_opt(argv[i], "-n");
        if (result != OPTTP_UNK) {
            any_opt = true;
        }
        if (result == OPTTP_SKIP) {
            // any_known = true;
            continue;
        }
        if (result == OPTTP_FILE) {
            // any_known = true;
            opts.input_type = IT_FILE;
            /* infile = argv[i]; */ add_file(argv[i]);
            continue;
        }
        if (result == OPTTP_OPT) {
            // any_known = true;
            opts.sort_comparison = SC_NUMERIC;
            continue;
        }

        result = get_opt(argv[i], "-R");
        if (result != OPTTP_UNK) {
            any_opt = true;
        }
        if (result == OPTTP_SKIP) {
            // any_known = true;
            continue;
        }
        if (result == OPTTP_FILE) {
            // any_known = true;
            opts.input_type = IT_FILE;
            /* infile = argv[i]; */ add_file(argv[i]);
            continue;
        }
        if (result == OPTTP_OPT) {
            // any_known = true;
            opts.sort_comparison = SC_RANDOM;
            opts.strict = false;
            continue;
        }

        result = get_opt(argv[i], "--random-sort");
        if (result != OPTTP_UNK) {
            any_opt = true;
        }
        if (result == OPTTP_SKIP) {
            // any_known = true;
            continue;
        }
        if (result == OPTTP_FILE) {
            // any_known = true;
            opts.input_type = IT_FILE;
            /* infile = argv[i]; */ add_file(argv[i]);
            continue;
        }
        if (result == OPTTP_OPT) {
            // any_known = true;
            opts.sort_comparison = SC_RANDOM;
            opts.strict = false;
            continue;
        }

        result = get_opt(argv[i], "--numeric");
        if (result != OPTTP_UNK) {
            any_opt = true;
        }
        if (result == OPTTP_SKIP) {
            // any_known = true;
            continue;
        }
        if (result == OPTTP_FILE) {
            // any_known = true;
            opts.input_type = IT_FILE;
            /* infile = argv[i]; */ add_file(argv[i]);
            continue;
        }
        if (result == OPTTP_OPT) {
            // any_known = true;
            opts.sort_comparison = SC_NUMERIC;
            continue;
        }

        result = get_opt(argv[i], "-r");
        if (result != OPTTP_UNK) {
            any_opt = true;
        }
        if (result == OPTTP_SKIP) {
            // any_known = true;
            continue;
        }
        if (result == OPTTP_FILE) {
            // any_known = true;
            opts.input_type = IT_FILE;
            /* infile = argv[i]; */ add_file(argv[i]);
            continue;
        }
        if (result == OPTTP_OPT) {
            // any_known = true;
            opts.reversed_sort = true;
            continue;
        }

        result = get_opt(argv[i], "--reverse");
        if (result != OPTTP_UNK) {
            any_opt = true;
        }
        if (result == OPTTP_SKIP) {
            // any_known = true;
            continue;
        }
        if (result == OPTTP_FILE) {
            // any_known = true;
            opts.input_type = IT_FILE;
            /* infile = argv[i]; */ add_file(argv[i]);
            continue;
        }
        if (result == OPTTP_OPT) {
            // any_known = true;
            opts.reversed_sort = true;
            continue;
        }

        result = get_opt(argv[i], "-v");
        if (result != OPTTP_UNK) {
            any_opt = true;
        }
        if (result == OPTTP_SKIP) {
            // any_known = true;
            continue;
        }
        if (result == OPTTP_FILE) {
            // any_known = true;
            opts.input_type = IT_FILE;
            /* infile = argv[i]; */ add_file(argv[i]);
            continue;
        }
        if (result == OPTTP_OPT) {
            // any_known = true;
            opts.output_type = OT_VERSION;
            continue;
        }
        result = get_opt(argv[i], "--version");
        if (result != OPTTP_UNK) {
            any_opt = true;
        }
        if (result == OPTTP_SKIP) {
            // any_known = true;
            continue;
        }
        if (result == OPTTP_FILE) {
            // any_known = true;
            opts.input_type = IT_FILE;
            /* infile = argv[i]; */ add_file(argv[i]);
            continue;
        }
        if (result == OPTTP_OPT) {
            // any_known = true;
            opts.output_type = OT_VERSION;
            continue;
        }

        if (!any_opt && argv[i][0] == '-') {
            show_usage_and_exit(1);
        } else if (!any_opt) {
            opts.input_type = IT_FILE;
            /*
            infile = argv[i];
            *//*
            if (input_files_count + 1 > MAX_INPUT_FILES) {
                die("too many input files");
            }
            opts.input_files[input_files_count] = argv[i];
            opts.input_files[input_files_count + 1] = NULL;
            ++input_files_count;*/
            add_file(argv[i]);
        }
    }
    /*
    if (opts.input_type == IT_FILE) {
        if (infile == NULL) {
            show_usage_and_exit(1);
        } else {
            if (input_files_count + 1 > MAX_INPUT_FILES) {
                die("too many input files");
            }
            opts.input_files[input_files_count] = infile;
            opts.input_files[input_files_count + 1] = NULL;
            ++input_files_count;
        }
    }
    */

    if (opts.input_type == IT_FILE && opts.input_files[0] == NULL) {
        show_usage_and_exit(1);
    }
}
