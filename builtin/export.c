#include "builtin.h"

// Allowed functions: readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

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
        if (ft_getenv(key, envp) == NULL)
            ft_setenv(key, value, envp);
        else
            ft_setenv(key, value, envp);
        free(key);
        i++;
    }
    return (0);
}

