#include "../parsing2.h"

void    free_argv(char **argv)
{
    int i;

    i = 0;
    while (argv[i])
        free(argv[i++]);
    free(argv);
}