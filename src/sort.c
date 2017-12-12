#include <mysort/sort.h>
#include <mysort/types.h>
//#include <mysort/funcs/comp.h>
//#include <mysort/funcs/sort.h>
#include <stdlib.h>
#include <stdio.h>
#include <mysort/die.h>
#include <mysort/args.h>
#include <string.h>

/*
static size_t bufsize = 1024, bufdiff = bufsize;
static void read_data(char **buf)
{
    *buf = malloc(bufsize);
    if (*buf == NULL)
    {
        die("memory allocation error (at read_data)");
    }

    FILE *in;

    if (opts.input_type == IT_STDIN)
    {
        in = fopen("/dev/stdin", "rb");
        if (in == NULL)
        {
            free(*buf);
            die("unable to open /dev/stdin (at read_data)");
        }
    }
    else
    {
        in = fopen(opts.input_file, "rb");
        if (in == NULL)
        {
            free(*buf);
            die("unable to open input file (at read_data)");
        }
    }

    size_t bytes = 0;
    while (true)
    {
        bytes = fread(*buf, 1, bufdiff, in);
        if (bytes != bufdiff)
        {
            bufsize -= bufdiff - bytes;
            break;
        }
        else
        {
            bufdiff = bufsize;
            bufsize *= 2;
            *buf = realloc(*buf, bufsize);
            if (*buf == NULL)
            {
                fclose(in);
                die("memory reallocation error (at read_data)");
            }
        }
    }
    fclose(in);
    return bufsize;
}

static size_t get_strs(char *buf, size_t bufsize, char ***strs)
{
    if (buf == NULL)
    {
        die("buf is NULL (at get_strs)");
    }

    size_t count = 0;
    for (size_t i = 0; i < bufsize; ++i)
    {
        if (buf[i] == '\n')
        {
            ++count;
        }
    }
    *strs = malloc(count * sizeof(char *));
    int begin = 0;
    for (size_t i = 0; i < bufsize; ++i)
    {

    }
}
*/

compare_t cf_normal(char *first, char *second)
{
    compare_t cmp = (compare_t) strcmp(first, second);
    if (cmp < 0)
    {
        return CMP_LESS;
    }
    else if (cmp == 0)
    {
        return CMP_EQ;
    }
    else
    {
        return CMP_MORE;
    }
}

void sf_comb(char **data, int count, compfunc_t cmp)
{
    //printf(">>%d\n", count);
    if (data == NULL)
    {
        die("data == NULL (at sf_comb)");
    }
    for (int i = 0; i < count; ++i)
    {
        for (int j = 0; j < count - 1; ++j)
        {
            //printf(">>>%d\n", cmp(data[j], data[j+1]));
            if (cmp(data[j], data[j+1]) == CMP_MORE)
            {
                //printf("    swap(data[%d{,+1}])\n", j);
                char *tmp = data[j];
                data[j] = data[j+1];
                data[j+1] = tmp;
            }
        }
    }
}

static compfunc_t get_comparator_func()
{
    switch (opts.sort_comparison)
    {
        case SC_NORMAL:
            return cf_normal;
            break;
        case SC_NUMERIC:
            //return cf_numeric;
            return cf_normal;
            break;
        default:
            return cf_normal;
            break;
    }
}

static sortfunc_t get_sort_func()
{
    return sf_comb;
}

static void write_data(char **strs, size_t count)
{
    if (strs == NULL)
    {
        die("strs == NULL (at write_data)");
    }

    for (size_t i = 0; i < count; ++i)
    {
        if (strs[i] == NULL)
        {
            die("strs[i] == NULL (at write_data)");
        }
        printf("%s", strs[i]);
    }
}

void sort_process()
{
/*    char *buf;
    size_t bufsize = read_data(&buf);
    char **strs;
    size_t count = get_strs(buf, bufsize, &strs);
    free(buf);*/
    int count = 0;
    char **strs = NULL;

    FILE *in;

    if (opts.input_type == IT_STDIN)
    {
        in = fopen("/dev/stdin", "r");
        if (in == NULL)
        {
            //free(*buf);
            die("unable to open /dev/stdin (at read_data)");
        }
    }
    else
    {
        in = fopen(opts.input_file, "r");
        if (in == NULL)
        {
            //free(*buf);
            die("unable to open input file (at read_data)");
        }
    }

    while (true)
    {
        ++count;
        strs = realloc(strs, count * sizeof(char*));
        if (strs == NULL)
        {
            die("memory allocation error");
        }
        strs[count-1] = malloc(65536);
        fgets(strs[count-1], 65536, in);
//        printf("count = %d, str = '%s'\n", count, strs[count-1]);
        if (feof(in))
        {
            fclose(in);
            break;
        }
    }

    compfunc_t compfunc = get_comparator_func();
    sortfunc_t sortfunc = get_sort_func();
    //sort_data(strs, count, compfunc, sortfunc);
    sortfunc(strs, count, compfunc);
    write_data(strs, count);
    for (int i = 0; i < count; ++i)
    {
        free(strs[i]);
    }
    free(strs);
}
