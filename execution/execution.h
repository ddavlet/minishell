
#ifndef EXECUTION_H
# define EXECUTION_H

# include "../parsing/parsing.h"
# include "../libft/libft.h"

# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <readline/readline.h>

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
*   redirections
*/
int	determine_output_fd(t_cmd *cmd, int out_fd);
int	determine_input_fd(t_cmd *cmd, int in_fd);
int handle_here_document(const char *delimiter);

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
