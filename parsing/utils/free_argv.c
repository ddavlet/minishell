#include "../parsing.h"

void    free_argv(const char **argv)
{
    int i;

    i = 0;
    while (argv[i])
        free((void *)argv[i++]);
    free((void *)argv);
}