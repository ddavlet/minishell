#include "builtin.h"

// The builtin_export function should add
//  or modify the environment variable. If the variable does not exist, 
//  it should be added. If the variable exists, it should be modified. 
//  The function should return 0 on success and 1 on failure. 
int    builtin_export(char **args, char **envp);
// The args parameter is an array of strings that contains the arguments.
//  The envp parameter is an array of strings that contains the environment variables.
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



