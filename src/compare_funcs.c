#include <mysort/compare_funcs.h>
#include <mysort/types.h>
#include <mysort/die.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

compare_t cf_normal(const char *first, const char *second) {
    if (first == NULL || second == NULL) {
        die ("argument is NULL (at cf_normal)");
    }
    compare_t cmp = (compare_t) strcmp(first, second);
    if (cmp < 0) {
        return CMP_LESS;
    } else if (cmp == 0) {
        return CMP_EQ;
    } else {
        return CMP_MORE;
    }
}

compare_t cf_numeric(const char *first, const char *second) {
    if (first == NULL || second == NULL) {
        die ("argument is NULL (at cf_numeric)");
    }
    bool eqlennumflag = false;
    for (int i = 0; ; ++i) {

        if (isdigit(first[i]) && isdigit(second[i]) && !eqlennumflag) {
            int j1 = i;
            int j2 = i;
            while (first[j1] != '\0' && isdigit(first[j1])) {
                ++j1;
            }
            while (second[j2] != '\0' && isdigit(second[j2])) {
                ++j2;
            }
            if (j1 < j2) {
                return CMP_LESS;
            } else if (j1 > j2) {
                return CMP_MORE;
            } else {
                eqlennumflag = true;
            }
        }
        if (first[i] == '\0' && second[i] == '\0') {
            return CMP_EQ;
        } else if (first[i] < second[i]) {
            return CMP_LESS;
        } else if (first[i] > second[i]) {
            return CMP_MORE;
        }
        if (!isdigit(first[i])) {
            eqlennumflag = false;
        }
    }
}

static int get_pow10_suffix_value(char c) {
    switch (c) {
    case 'K': case 'k':
        return 3;
    case 'M': case 'm':
        return 6;
    case 'G': case 'g':
        return 9;
    case 'T': case 't':
        return 12;
    case 'P': case 'p':
        return 15;
    case 'E': case 'e':
        return 18;
    case 'Z': case 'z':
        return 21;
    case 'Y': case 'y':
        return 24;
    default:
        return 0;
    }
}

compare_t cf_human_numeric(const char *first, const char *second) {
    if (first == NULL || second == NULL) {
        die ("argument is NULL (at cf_human_numeric)");
    }
    bool eqlennumflag = false;
    for (int i = 0; ; ++i) {
        if (isdigit(first[i]) && isdigit(second[i]) && !eqlennumflag) {
            int j1 = i;
            int j2 = i;
            while (first[j1] != '\0' && isdigit(first[j1])) {
                ++j1;
            }
            while (second[j2] != '\0' && isdigit(second[j2])) {
                ++j2;
            }

            /* Теперь небольшой хак: добавим нужное число виртуальных нулей */
            j1 += get_pow10_suffix_value(first[j1]);
            j2 += get_pow10_suffix_value(second[j2]);
            if (j1 < j2) {
                return CMP_LESS;
            } else if (j1 > j2) {
                return CMP_MORE;
            } else {
                eqlennumflag = true;
            }
        }

        if (first[i] == '\0' && second[i] == '\0') {
            return CMP_EQ;
        } else if (first[i] < second[i]) {
            return CMP_LESS;
        } else if (first[i] > second[i]) {
            return CMP_MORE;
        }

        if (!isdigit(first[i])) {
            eqlennumflag = false;
        }
    }
}

compare_t cf_random(const char *first, const char *second) {
    if (first == NULL || second == NULL) {
        die ("argument is NULL (at cf_numeric)");
    }
    if (strcmp(first, second) == 0) {
        return CMP_EQ;
    } else {
        return (rand() & (1 << 4)) ? CMP_LESS : CMP_MORE;
    }
}

compare_t reverse_compare(compare_t cmp) {
    return -cmp;
}

compare_t cf_reverse_normal(const char *first, const char *second) {
    return reverse_compare(cf_normal(first, second));
}
compare_t cf_reverse_numeric(const char *first, const char *second) {
    return reverse_compare(cf_numeric(first, second));
}
compare_t cf_reverse_human_numeric(const char *first, const char *second) {
    return reverse_compare(cf_human_numeric(first, second));
}
compare_t cf_reverse_random(const char *first, const char *second) {
    return reverse_compare(cf_random(first, second));
}

compfunc_t get_reverse_cf(compfunc_t cf) {
    if (cf == cf_normal) {
        return cf_reverse_normal;
    } else if (cf == cf_numeric) {
        return cf_reverse_numeric;
    } else if (cf == cf_random) {
        return cf_reverse_random;
    } else if (cf == cf_human_numeric) {
        return cf_reverse_human_numeric;
    } else {
        return cf_reverse_normal;
    }
}
