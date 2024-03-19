#ifndef BUILTIN_H
# define BUILTIN_H

# include "../libft/libft.h"
# include "../execution/execution.h"
# include "../parsing/parsing.h"

typedef struct s_executor	t_executor;

int		builtin_export(char **argv, t_env *root);
int		builtin_env(char **argv, t_env *root);
int		builtin_unset(char **argv, t_env *root);
int		builtin_pwd(char **argv, t_env *root);
int		builtin_echo(char **argv, t_env *root);
int		builtin_cd(char **argv, t_env *root);
int		builtin_exit(char **argv, t_env *root, t_executor *exec);


/*Utils*/
char	*ft_strcdup(const char *s, int c);
int		ft_isnumber(char *str);


/*Errors*/
int		builtin_err_gen(const char *cmd, const char *msg, const char *path);


#endif
