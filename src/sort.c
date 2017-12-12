#include <mysort/sort.h>
#include <mysort/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <mysort/die.h>
#include <mysort/args.h>
#include <string.h>
#include <ctype.h>

compare_t cf_normal(char *first, char *second)
{
    if (first == NULL || second == NULL)
    {
        die ("argument in NULL (at cf_normal)");
    }
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

compare_t cf_numeric(char *first, char *second)
{
    //printf("Hi\n");
    if (first == NULL || second == NULL)
    {
        die ("argument in NULL (at cf_numeric)");
    }
    bool eqlennumflag = false;
    for (int i = 0; ; ++i)
    {

        if (isdigit(first[i]) && isdigit(second[i]) && !eqlennumflag)
        {
            int j1 = i;
            int j2 = i;
            while (first[j1] != '\0' && isdigit(first[j1]))
            {
                ++j1;
            }
            while (second[j2] != '\0' && isdigit(second[j2]))
            {
                ++j2;
            }
            if (j1 < j2)
            {
                return CMP_LESS;
            }
            else if (j1 > j2)
            {
                return CMP_MORE;
            }
            else
            {
                eqlennumflag = true;
            }
        }
        if (first[i] == '\0' && second[i] == '\0')
        {
            return CMP_EQ;
        }
        else if (first[i] < second[i])
        {
            return CMP_LESS;
        }
        else if (first[i] > second[i])
        {
            return CMP_MORE;
        }
        if (!isdigit(first[i]))
        {
            eqlennumflag = false;
        }
    }

}

void sf_comb(char **data, int count, compfunc_t cmp)
{
    //printf(">>%d\n", count);
    if (data == NULL)
    {
        die("data == NULL (at sf_comb)");
    }

    int step = count - 1;
    while (step > 0)
    {
        for (int j = 0; j + step < count; ++j)
        {
            //printf(">>>%d\n", cmp(data[j], data[j+1]));
            if (cmp(data[j], data[j+step]) == CMP_MORE)
            {
                //printf("    swap(data[%d{,+1}])\n", j);
                char *tmp = data[j];
                data[j] = data[j+step];
                data[j+step] = tmp;
            }
        }
        step /= 1.2;
    }

    bool is_sorted = false;
    while (!is_sorted)
    {
        is_sorted = true;
        for (int j = 0; j < count - 1; ++j)
        if (cmp(data[j], data[j+1]) == CMP_MORE)
        {
            is_sorted = false;
            char *tmp = data[j];
            data[j] = data[j+1];
            data[j+1] = tmp;
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
            return cf_numeric;
            //return cf_normal;
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
