
#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"
//# include "../testing/testing.h"
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>


int	execution(t_pars **cmd_arr, char *envp[]);

/*
*   utils
*/
void	remove_inner_quotes(char **cmd);
void	msg_error(char *err);
void	free_string_arr(char **arr);
char	*get_path(char *cmd, char *envp[]);
char	*get_env_all_path(char *envp[]);

#endif
