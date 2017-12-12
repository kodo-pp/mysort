#ifndef MYSORT_TYPES_H
#define MYSORT_TYPES_H

#include <stdbool.h>

#define NORETURN __attribute__((noreturn))

typedef char * string_t;

enum opt_input_type
{
    IT_STDIN = 1,
    IT_FILE
};

enum opt_output_type
{
    OT_SORT = 1,
    OT_USAGE,
    OT_VERSION
};

enum opt_sort_comparison
{
    SC_NORMAL = 1,
    SC_NUMERIC = 2
};

struct _options_t
{
    int input_type;
    int output_type;
    int sort_comparison;
    string_t program_name;
    string_t input_file;
    bool invalid_flag;
};

typedef struct _options_t options_t;

#endif