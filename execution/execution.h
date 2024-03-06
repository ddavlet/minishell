
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

typedef struct s_scope
{
	int			scope_id;
	int			input_fd;
	int			output_fd;
	pid_t		pid;
	t_pipe		*pipe;
}				t_scope;

typedef struct s_executor
{
	int			command_index;
	int			status;
	t_cmd		**cmds;
}				t_executor;

int				execution(t_cmd **cmds);
int				shell(t_executor *exec, t_scope *scope);
int				execute_cmd(t_executor *exec, t_scope *scope);
int				execute_builtin(t_executor *exec, t_scope *scope);
int				execute_nested_scope(t_executor *exec, t_scope *scope);
t_pipe			*create_pipe(void);
t_scope			*create_nested_scope(t_executor *exec, t_scope *scope);
t_scope			*initialize_scope(void);
int				check_exit_value(t_executor *exec, t_scope *scope);
void			evaluate_and_or(t_executor *exec);
t_oper			operation_after(t_executor *exec, t_scope *scope);
t_oper			operation_before(t_executor *exec, t_scope *scope);
int				manage_input_output(t_executor *exec, t_scope *scope);

/*
 *	utils
 */
int				param_check(t_executor *exec, t_scope *scope);
void			exit_handler(int status);
char			*get_path(char *cmd, char *envp[]);
void			msg_error(char *err);
void			free_arr2d(void **arr2d);
void			terminate(t_executor *exec, t_scope *scope, int status);
char			*get_name(char *cmd_path);
int				is_builtin(t_executor *exec);
int				is_inside_scope(t_executor *exec, t_scope *scope);
int				has_nested_scope(t_executor *exec, t_scope *scope);
int				connected_through_operation(t_cmd *comparison, t_cmd *other);
int				arr_len(char **arr);
t_cmd			*current_cmd_in_execution(t_executor *exec);
t_cmd			*previous_cmd_in_execution(t_executor *exec);
t_cmd			*next_cmd_in_execution(t_executor *exec);
int				find_nested_id(t_executor *exec, t_scope *scope);
int				most_inside_scope(int *scope_stack);
t_cmd			*last_cmd_in_scope(t_executor *exec, t_scope *scope);
t_cmd			*next_command(t_executor *exec, t_cmd *cmd);
t_cmd			*last_cmd_in_execution(t_executor *exec);
int				get_scope(t_cmd *cmd);
int				get_outside_scope(t_cmd *cmd);

/*
 *   io_redirections
 */
int				last_output_redir(t_executor *exec);
int				last_input_redir(t_executor *exec, t_scope *scope);
int				handle_here_document(const char *delimiter, t_env *env,
					t_scope *scope);
int				handle_truncate_redirection(const char *file_name);
int				handle_append_redirection(const char *file_name);
int				handle_input_redirection(const char *file_name);

/*
 *   debugging
 */
void			print_exit_info(int status);
t_cmd			**mockup_three_cmds(t_env *env);
t_cmd			**mockup_single_cmd(char *env[]);
t_cmd			**mockup(void);

#endif
