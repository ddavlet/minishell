
#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"
# include "../testing/testing.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		execution(t_com **cmd_arr, char *envp[]);

/*
 *	utils
 */
int		count_cmds(t_com **cmds);
char	*get_env_all_path(char *envp[]);
char	*get_path(char *cmd, char *envp[]);
void	free_string_arr(char **arr);
void	msg_error(char *err);
void	remove_inner_quotes(char **cmd);

#endif
