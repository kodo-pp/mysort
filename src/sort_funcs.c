#include <mysort/sort_funcs.h>
#include <mysort/die.h>
#include <stdlib.h>

void sf_comb(char **data, int count, compfunc_t cmp)
{
    if (data == NULL)
    {
        die("data == NULL (at sf_comb)");
    }

    int step = count - 1;
    while (step > 0)
    {
        for (int j = 0; j + step < count; ++j)
        {
            if (cmp(data[j], data[j+step]) == CMP_MORE)
            {
                char *tmp = data[j];
                data[j] = data[j+step];
                data[j+step] = tmp;
            }
        }
        step /= 1.2473309;
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
