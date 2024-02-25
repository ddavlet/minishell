
#ifndef EXECUTION_H
# define EXECUTION_H

# include "../libft/libft.h"
# include "../parsing/parsing.h"
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_fd_state
{
	int			fd;
	int			is_open;
	char		*purpose;
}				t_fd_state;

typedef struct s_executor
{
	int			in_fd;
	int			out_fd;
	int			pipe_fd[2];
	int			status;
	int			fd_count;
	pid_t		pid;
	t_fd_state	*fd_states;
	t_cmd		**cmds;
}				t_executor;

int				execution(t_cmd **cmds, char *envp[]);
int				execute_command(char *argv[], char *envp[]);
int				execute_loop(t_executor *executor);
int				ft_mkstemp(char *template);
int				child_process(t_executor *executor, int cmd_index);
int				parent_process(t_executor *executor, int cmd_index);

/*
 *	utils
 */
char			*get_path(char *cmd, char *envp[]);
void			msg_error(char *err);
void			free_arr2d(void **arr2d);
unsigned long	rand_simple(void);

/*
 *   io_redirections
 */
int				find_last_output_redir(t_executor *executor, int cmd_index);
int				find_last_input_redir(t_executor *executor, int cmd_index);
int				handle_here_document(const char *delimiter, t_env *env,
					t_executor *executor);
int				handle_truncate_redirection(const char *file_name);
int				handle_append_redirection(const char *file_name);
int				handle_input_redirection(const char *file_name);

/*
 *   cleaners
 */
void			terminate_execution(t_executor *executor);

/*
 *   debugging
 */
t_cmd			**mockup_three_cmds(void);
t_cmd			**mockup_single_cmd(char *env[]);
t_cmd			**mockup(void);

#endif
