#include <mysort/sort.h>
#include <mysort/types.h>
#include <mysort/die.h>
#include <mysort/args.h>
#include <mysort/compare_funcs.h>
#include <mysort/sort_funcs.h>
#include <mysort/vec.h>
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

    for (size_t i = 0; i < count; ++i) {
        if (strs[i] == NULL) {
            die("strs[i] == NULL (at write_data)");
        }
        printf("%s", strs[i]);
    }
}

static struct vec *read_input_files() {
    struct vec *strs = malloc(sizeof (struct vec));
    if (!strs) {
        die("malloc() failed (at read_input_files())");
    }
    make_vec(strs);

    FILE *in;

    if (opts.input_type == IT_STDIN) {
        char *tmp = malloc(100 * sizeof(char));
        if (!tmp) {
            die("tmp allocation failed");
        }
        strncpy(tmp, "/dev/stdin", 99);
        fprintf(stderr, "Appending '%s'\n", tmp);
        if (vec_append(&opts.input_files, tmp) != VEC_OK) {
            die("unable to append '/dev/stdin' to input files list");
        }
        //in = fopen("/dev/stdin", "r");
        //if (in == NULL) {
        //    die("unable to open /dev/stdin (at read_data)");
        //}
    /*
    } else {
        in = fopen(opts.input_file, "r");
        if (in == NULL) {
            die("unable to open input file (at read_data)");
        }
    }*/
    }
    for (size_t i = 0; i < opts.input_files.length; ++i) {
        fprintf(stderr, "i = %d, len = %d\n", (int)i, (int)strs->length);
        in = fopen(vec_get(&opts.input_files, i), "r");
        if (!in) {
            fprintf(stderr, "AAA '%s'\n", vec_get(&opts.input_files, i));
            die("Unable to open file");
        }
        while (true) {
            char *tmp = NULL;
            size_t length = 0;
            getline(&tmp, &length, in);
            if (!tmp) {
                die("getline() failed");
            }

            if (vec_append(strs, tmp) != VEC_OK) {
                die("unable to add input string");
            }

            //free(tmp);

            if (feof(in)) {
                fclose(in);
                break;
            }
        }
    }
    return strs;
}

void sort_process() {
    struct vec *v = read_input_files();
    char **strs = v->data;

    compfunc_t compfunc = get_comparator_func();
    sortfunc_t sortfunc = get_sort_func();
    sortfunc((const char**)strs, v->length, compfunc);
    write_data(strs, v->length);
    for (size_t i = 0; i < v->length; ++i) {
        free(strs[i]);
    }
    //free(strs);
}
