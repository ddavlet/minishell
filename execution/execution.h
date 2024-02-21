
#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "../parsing/parsing.h"
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define TEMPLATE_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"

typedef struct s_executor
{
	int			in_fd;
	int			out_fd;
	int			pipe_fd[2];
	int			pid;
	int			status;
	t_cmd		**cmds;
	char		**envp;
}				t_executor;

int				execute_command_line(t_cmd **cmd_arr, char *envp[]);

/*
 *	utils
 */
char			*get_env_all_path(char *envp[]);
char			*get_path(char *cmd, char *envp[]);
void			remove_inner_quotes(char **cmd);
void			msg_error(char *err);
void			free_string_arr(char **arr);
unsigned long	rand_simple(void);

/*
 *   redirections
 */
int				determine_output_fd(t_cmd *cmd, int out_fd);
int				determine_input_fd(t_cmd *cmd, int in_fd);
int				handle_here_document(const char *delimiter);

/*
 *   cleaners
 */
void			terminate_execution(t_cmd **cmds, char *envp[]);

/*
 *   debugging
 */
t_cmd			**mockup_ls_grep_wc(void);
t_cmd			**mockup_single_cmd(void);
t_cmd			**mockup_empty_cmds(void);

#endif
