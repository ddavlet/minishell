
#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"
# include "../libft/libft.h"

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		execute_command_line(t_cmd **cmd_arr, char *envp[]);

/*
 *	utils
 */
char	*get_env_all_path(char *envp[]);
char	*get_path(char *cmd, char *envp[]);
void	remove_inner_quotes(char **cmd);
void	msg_error(char *err);
void	free_string_arr(char **arr);

/*
*   cleaners
*/
void	terminate_execution(t_cmd **cmds, char *envp[]);

/*
*   debugging
*/
t_cmd   **mockup_ls_grep_wc(void);
t_cmd **mockup_single_cmd(void);
t_cmd   **mockup_empty_cmds(void);


#endif
