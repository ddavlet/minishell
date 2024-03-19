#ifndef BUILTIN_H
#define BUILTIN_H

#include "../parsing/parsing.h"
#include <stddef.h>

int		builtin_export(char **argv, t_env *root);
int		builtin_env(char **argv, t_env *root);
int		builtin_unset(char **argv, t_env *root);
int		builtin_pwd(char **argv, t_env *root);
int		builtin_echo(char **argv, t_env *root);
int		builtin_cd(char **argv, t_env *root);
int		builtin_exit(char **argv, t_env *root);


/*Utils*/
char	*ft_strcdup(const char *s, int c);
int		ft_isnumber(char *str);


/*Errors*/
int		builtin_err_gen(const char *cmd, const char *msg, const char *path);


#endif
