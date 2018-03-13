#include <mysort/compare_funcs.h>
#include <mysort/types.h>
#include <mysort/die.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

compare_t cf_normal(char *first, char *second) {
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

compare_t cf_numeric(char *first, char *second) {
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
