#include <mysort/sort_funcs.h>
#include <mysort/die.h>
#include <mysort/args.h>
#include <stdlib.h>

void sf_comb(const char **data, int count, compfunc_t cmp) {
    if (data == NULL) {
        die("data == NULL (at sf_comb)");
    }

    int step = count - 1;
    while (step > 0) {
        for (int j = 0; j + step < count; ++j) {
            if (cmp(data[j], data[j+step]) == CMP_MORE) {
                const char *tmp = data[j];
                data[j] = data[j+step];
                data[j+step] = tmp;
            }
        }
        step /= 1.2473309;
    }

    if (opts.strict) {
        bool is_sorted = false;
        while (!is_sorted) {
            is_sorted = true;
            for (int j = 0; j < count - 1; ++j) {
                if (cmp(data[j], data[j+1]) == CMP_MORE) {
                    is_sorted = false;
                    const char *tmp = data[j];
                    data[j] = data[j+1];
                    data[j+1] = tmp;
                }
            }
        }
    }
}

void sf_insertion(const char **data, int count, compfunc_t cmp) {
    if (data == NULL) {
        die("data == NULL (at sf_insertion)");
    }

    for (int i = 0; i < count; ++i) {
        int j = i;
        while (j != 0 && cmp(data[j-1], data[j]) == CMP_MORE) {
            const char *tmp = data[j-1];
            data[j-1] = data[j];
            data[j] = tmp;
            --j;
        }
    }
}
