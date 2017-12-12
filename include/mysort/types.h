#ifndef MYSORT_TYPES_H
#define MYSORT_TYPES_H

#include <stdbool.h>

#define __attribute__((noreturn)) NORETURN

typedef char * string_t;

#define IT_STDIN 1
#define IT_FILE 2

#define OT_SORT 1
#define OT_USAGE 2

struct _options_t
{
    int input_type;
    int output_type;
    string_t program_name;
    string_t input_file;
    bool invalid_flag;
};

typedef struct _options_t options_t;

#endif
