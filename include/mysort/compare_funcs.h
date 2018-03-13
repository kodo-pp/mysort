#ifndef MYSORT_COMPARE_FUNCS_H
#define MYSORT_COMPARE_FUNCS_H

#include <mysort/types.h>

compare_t cf_normal(char *, char *);
compare_t cf_numeric(char *, char *);
compfunc_t get_reverse_cf(compare_t);

#endif
