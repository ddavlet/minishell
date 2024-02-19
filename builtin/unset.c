#include "builtin.h"

int    builtin_unset(char **args, char **envp)
{
    int i;
    int j;
    int ret;

    i = 1;
    while (args[i])
    {
        j = 0;
        while (args[i][j] && args[i][j] != '=')
            j++;
        if (args[i][j] == '=')
        {
            ret = ft_unsetenv(args[i], envp);
            if (ret == -1)
                return (1);
        }
        else
        {
            ret = ft_unsetenv(args[i], envp);
            if (ret == -1)
                return (1);
        }
        i++;
    }
    return (0);
}
