#include <mysort/sort.h>
#include <mysort/types.h>
#include <mysort/die.h>
#include <mysort/args.h>
#include <mysort/compare_funcs.h>
#include <mysort/sort_funcs.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

static compfunc_t get_comparator_func() {
    switch (opts.sort_comparison) {
    case SC_NORMAL:
        return opts.reversed_sort ? get_reverse_cf(cf_normal) : cf_normal;
        break;
    case SC_NUMERIC:
        return opts.reversed_sort ? get_reverse_cf(cf_numeric) : cf_numeric;
        break;
    case SC_HUMAN_NUMERIC:
        return opts.reversed_sort ? get_reverse_cf(cf_human_numeric) : cf_human_numeric;
        break;
    case SC_RANDOM:
        return opts.reversed_sort ? get_reverse_cf(cf_random) : cf_random;
        break;
    default:
        return opts.reversed_sort ? get_reverse_cf(cf_normal) : cf_normal;
        break;
    }
}

static sortfunc_t get_sort_func() {
    return sf_comb;
}

static void write_data(char **strs, size_t count) {
    if (strs == NULL) {
        die("strs == NULL (at write_data)");
    }

    //printf("count = %zu\n", count);

    FILE *outfile = stdout;
    if (opts.output_filename != NULL) {
        outfile = fopen(opts.output_filename, "w");
        if (outfile == NULL) {
            die("unable to open output file");
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (strs[i] == NULL) {
            die("strs[i] == NULL (at write_data)");
        }
        fprintf(outfile, "%s", strs[i]);
    }

    if (outfile != stdout && outfile != NULL) {
        fclose(outfile);
    }
}

void immediate_sort_iter(compfunc_t compfunc, const char **strs, int count) {
    if (strs == NULL) {
        die("strs == NULL (at immediate_sort_iter)");
    }
    int j = count - 1;
    while (j > 0 && compfunc(strs[j], strs[j - 1]) == CMP_LESS) {
        const char *tmp = strs[j];
        strs[j] = strs[j - 1];
        strs[j - 1] = tmp;
        --j;
    }
}

void immediate_sort_process() {
    int count = 0;
    int capacity = 0;
    char **strs = NULL;
    compfunc_t compfunc = get_comparator_func();

    while (true) {
        ++count;
        if (strs == NULL || count > capacity) {
            capacity *= 2;
            if (count > capacity) {
                capacity = count;
            }
            char **tmp = realloc(strs, capacity * sizeof(char*));
            if (tmp == NULL) {
                die("memory allocation error (at immediate_sort_process)");
            }
            strs = tmp;
        }
        if (strs == NULL) {
            die("memory allocation error (at immediate_sort_process)");
        }

        size_t length = 0;
        ssize_t read = getline(&strs[count-1], &length, stdin);
        if (read == -1) {
            --count;
        }

        immediate_sort_iter(compfunc, (const char **)strs, count);
        if (feof(stdin)) {
            break;
        }
    }

    write_data(strs, count);
    /* i <= count, NOT i < count (the second one causes memory leak!) */
    for (int i = 0; i <= count; ++i) {
        if (strs[i] != NULL) {
            free(strs[i]);
        }
    }
    free(strs);
}

void sort_process() {
    int count = 0;
    int capacity = 0;
    char **strs = NULL;
/*
    if (opts.input_type == IT_STDIN) {
        in = fopen("/dev/stdin", "r");
        if (in == NULL) {
            die("unable to open /dev/stdin (at read_data)");
        }
    } else {
        in = fopen(opts.input_file, "r");
        if (in == NULL) {
            die("unable to open input file (at read_data)");
        }
    }
*/
    if (opts.input_type == IT_STDIN) {
        assert(MAX_INPUT_FILES >= 1);
        opts.input_files[0] = "/dev/stdin";
        opts.input_files[1] = NULL;
    }

    int fileno = 0;
    while (fileno <= MAX_INPUT_FILES && opts.input_files[fileno] != NULL) {
        //fprintf(stderr, "Opening '%s'\n", opts.input_files[fileno]);
        FILE *in = fopen(opts.input_files[fileno], "r");
        ++fileno;
        if (in == NULL) {
            die("unable to open input file (at sort_process)");
        }
        while (true) {
            ++count;
            if (strs == NULL || count > capacity) {
                capacity *= 2;
                if (count > capacity) {
                    capacity = count;
                }
                char **tmp = realloc(strs, capacity * sizeof(char*));
                if (tmp == NULL) {
                    die("memory allocation error (at sort_process)");
                }
                strs = tmp;
            }
            if (strs == NULL) {
                die("memory allocation error (at sort_process)");
            }
            /*
            strs[count-1] = malloc(65536);
            fgets(strs[count-1], 65536, in);
            */

            size_t length = 0;
            ssize_t read = getline(&strs[count-1], &length, in);
            if (read == -1) {
                --count;
            }
            //printf("999: got str: '%s' (%zx), count = %d, length = %zd\n", strs[count - 1], (size_t)strs[count - 1], count, read);

            if (feof(in)) {
                fclose(in);
                break;
            }
        }
    }
    //printf("9count = %d\n", count);

    compfunc_t compfunc = get_comparator_func();
    sortfunc_t sortfunc = get_sort_func();
    sortfunc((const char**)strs, count, compfunc);
    write_data(strs, count);
    /* i <= count, NOT i < count (the second one causes memory leak!) */
    for (int i = 0; i <= count; ++i) {
        if (strs[i] != NULL) {
            free(strs[i]);
        }
    }
    free(strs);
}
