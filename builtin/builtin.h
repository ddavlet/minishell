#ifndef BUILTIN_H
# define BUILTIN_H

# include <stddef.h>

int    builtin_cd(char **args, char **envp);
int    builtin_echo(char **args);
int    builtin_env(char **envp);
int    builtin_exit(char **args);
int    builtin_export(char **args, char **envp);
int    builtin_pwd(char **envp);
int    builtin_unset(char **args, char **envp);

#endif