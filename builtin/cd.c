#include "builtin.h"

int    builtin_cd(t_com *com, char *envp[])
{
    char	*path;
    int		ret;

    if (com->args[1] == NULL)
    {
        path = ft_getenv("HOME", envp);
        if (path == NULL)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (1);
        }
    }
    else
        path = com->args[1];
    ret = chdir(path);
    if (ret == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return (1);
    }
    return (0);
}