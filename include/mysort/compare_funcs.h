#ifndef MYSORT_COMPARE_FUNCS_H
#define MYSORT_COMPARE_FUNCS_H

#include <mysort/types.h>

compare_t cf_normal(const char *, const char *);
compare_t cf_numeric(const char *, const char *);
compfunc_t get_reverse_cf(compfunc_t);

#endif
