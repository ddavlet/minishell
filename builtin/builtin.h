#ifndef BUILTIN_H
# define BUILTIN_H

# include <stddef.h>
# include "../parsing/parsing.h"

int    builtin_cd(t_com *com, char *envp[]);
int    builtin_echo(char **args);
int    builtin_env(char **envp);
int    builtin_exit(char **args);
int    builtin_export(char **args, char **envp);
int    builtin_pwd(char **envp);
int    builtin_unset(char **args, char **envp);

/*
*   utils
*/
void    ft_setenv(char *key, char *value, char **envp);
char    *ft_strcdup(const char *s, int c);
int ft_unsetenv(char *key, char **envp);
void    ft_setenv(char *key, char *value, char **envp);


#endif