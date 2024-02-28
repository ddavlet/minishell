
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
}				t_fd_state;

typedef struct s_pipe
{
	int			*pipe_fd;
	t_fd_state	*read;
	t_fd_state	*write;
}				t_pipe;

typedef struct s_context
{
	int			context_depth;
	int			input_fd;
	int			output_fd;
	int			status;
	pid_t		pid;
	t_pipe		*pipe;
	t_oper		oper_before;
	t_oper		oper_after;
}				t_context;

typedef struct s_executor
{
	int			command_index;
	t_cmd		**cmds;
}				t_executor;

int				execution(t_cmd **cmds);
int				execute_command(char *argv[], char *envp[]);
int				execute_context(t_executor *exec, t_context *context);
int				ft_mkstemp(char *template);
int				child_process(t_executor *exec, t_context *context);
t_pipe			*create_pipe(void);
t_context		*create_subcontext(t_executor *exec, t_context *context);

/*
 *	utils
 */
char			*get_path(char *cmd, char *envp[]);
void			msg_error(char *err);
void			free_arr2d(void **arr2d);
unsigned long	rand_simple(void);
int				cmds_size(void **cmds);
t_logic_op		*initialize_priority_stack(t_cmd **cmds);
t_logic_op		*push_stack(t_logic_op *priority_stack, t_logic_op op);
t_logic_op		pop_stack(t_logic_op *priority_stack);

/*
 *   io_redirections
 */
int				last_output_redir(t_executor *exec);
int				last_input_redir(t_executor *exec);
int				handle_here_document(const char *delimiter, t_env *env,
					t_executor *exec);
int				handle_truncate_redirection(const char *file_name);
int				handle_append_redirection(const char *file_name);
int				handle_input_redirection(const char *file_name);

/*
 *   cleaners
 */
void			terminate_execution(t_executor *exec);

/*
 *   debugging
 */
t_cmd			**mockup_three_cmds(void);
t_cmd			**mockup_single_cmd(char *env[]);
t_cmd			**mockup(void);

#endif
