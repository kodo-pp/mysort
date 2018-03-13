#include <mysort/sort.h>
#include <mysort/types.h>
#include <mysort/die.h>
#include <mysort/args.h>
#include <mysort/compare_funcs.h>
#include <mysort/sort_funcs.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

static compfunc_t get_comparator_func() {
    switch (opts.sort_comparison) {
    case SC_NORMAL:
        return /*opts.reversed_sort ?*/ cf_normal;
        break;
    case SC_NUMERIC:
        return cf_numeric;
        break;
    default:
        return cf_normal;
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

    for (size_t i = 0; i < count; ++i) {
        if (strs[i] == NULL) {
            die("strs[i] == NULL (at write_data)");
        }
        printf("%s", strs[i]);
    }
}

void sort_process() {
    int count = 0;
    char **strs = NULL;

    FILE *in;

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

    while (true) {
        ++count;
        strs = realloc(strs, count * sizeof(char*));
        if (strs == NULL) {
            die("memory allocation error");
        }
        strs[count-1] = malloc(65536);
        fgets(strs[count-1], 65536, in);
        if (feof(in)) {
            fclose(in);
            break;
        }
    }

    compfunc_t compfunc = get_comparator_func();
    sortfunc_t sortfunc = get_sort_func();
    sortfunc(strs, count, compfunc);
    write_data(strs, count);
    for (int i = 0; i < count; ++i) {
        free(strs[i]);
    }
    free(strs);
}
