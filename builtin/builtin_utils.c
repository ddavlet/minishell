#include "builtin.h"
#include "../libft/libft.h"

char    *ft_strcdup(const char *s, int c)
{
    char    *str;
    int        i;

    i = 0;
    while (s[i] != c && s[i] != '\0')
        i++;
    str = (char *)malloc(sizeof(char) * (i + 1));
    if (str == NULL)
        return (NULL);
    i = 0;
    while (s[i] != c && s[i] != '\0')
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    return (str);

}

// ft_setenv should be declared as follows:
// void    ft_setenv(char *key, char *value, char **envp);

void    ft_setenv(char *key, char *value, char **envp)
{
    int    i;
    char    *new_envp;

    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
        {
            free(envp[i]);
            new_envp = ft_strjoin(key, "=");
            new_envp = ft_strjoin(new_envp, value);
            envp[i] = new_envp;
            return ;
        }
        i++;
    }
    new_envp = ft_strjoin(key, "=");
    new_envp = ft_strjoin(new_envp, value);
    envp[i] = new_envp;
    envp[i + 1] = NULL;
}

// ft_unsetenv is a function that removes an environment variable from the environment.
int ft_unsetenv(char *key, char **envp)
{
    int i;
    int j;
    int k;
    int len;

    i = 0;
    while (envp[i])
    {
        j = 0;
        while (envp[i][j] && envp[i][j] != '=')
            j++;
        if (envp[i][j] == '=')
        {
            len = ft_strlen(key);
            if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
            {
                k = i;
                while (envp[k])
                {
                    envp[k] = envp[k + 1];
                    k++;
                }
                return (0);
            }
        }
        i++;
    }
    return (-1);
}

int ft_isnumber(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (ft_isdigit(str[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}