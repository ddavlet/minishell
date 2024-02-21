#include "builtin.h"

int    builtin_export(char **args, char **envp)
{
    int    i;
    char    *key;
    char    *value;

    i = 1;
    while (args[i] != NULL)
    {
        key = ft_strcdup(args[i], '=');
        value = ft_strchr(args[i], '=');
        if (value == NULL)
        {
            free(key);
            return (1);
        }
        value++;
        if (getenv(key) == NULL)
            ft_setenv(key, value, envp); 
        else
            ft_setenv(key, value, envp); 
        free(key);
        i++;
    }
    return (0);
}



