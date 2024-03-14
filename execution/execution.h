#ifndef EXECUTION_H
# define EXECUTION_H

# define SCOPE 1
# include "../libft/libft.h"
# include "../parsing/parsing.h"
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_node
{
	t_pipe			*pipe;
	struct s_node	*next;
}					t_node;

typedef struct s_queue
{
	t_node			*front;
	t_node			*rear;
}					t_queue;

typedef struct s_fd_state
{
	int				fd;
	int				is_open;
	t_pipe			*pipe;
}					t_fd_state;

typedef struct s_pipe
{
	int				*pipe_fd;
	t_fd_state		*read;
	t_fd_state		*write;
}					t_pipe;

typedef struct s_executor
{
	pid_t			pid;
	int				status;
	int				command_index;
	char			**envp;
	t_cmd			**cmds;
	t_queue			*pipe_queue;
}					t_executor;

int					execution(t_cmd **cmds, char **envp);
void				set_io_streams(t_executor *exec);
int					execute(char **argv, char **envp);
int					execute_cmd(t_executor *exec);
int					execute_builtin(t_executor *exec);
int					execute_nested_scope(t_executor *exec);
t_pipe				*create_pipe(void);
t_scope				*create_nested_scope(t_executor *exec);
t_scope				*initialize_scope(t_executor *exec);
int					check_exit_value(t_executor *exec);
void				evaluate_logic_operator(t_executor *exec);
t_fd_state			*initialize_fd_state(int fd);

/*
 *	utils
 */
t_cmd				*current_cmd(t_executor *exec);
t_cmd				*next_cmd(t_executor *exec, t_cmd *cmd);
t_cmd				*previous_cmd(t_executor *exec, t_cmd *cmd);
int					connected_through_operation(t_cmd *cmd, t_cmd *other);
int					is_final(t_executor *exec);
int					enqueue_pipe(t_queue *queue, t_pipe *pipe);
t_pipe				*dequeue_pipe(t_queue *queue);
void				close_pipe(t_pipe *pipe);

int					param_check(t_executor *exec, t_scope *scope);
void				exit_handler(int status);
char				*get_path(char *cmd, char *envp[]);
void				msg_error(char *err);
void				free_arr2d(void **arr2d);
void				terminate(t_executor *exec, t_scope *scope, int status,
						char *msg);
char				*get_name(char *cmd_path);
int					is_builtin(t_executor *exec);
int					is_inside_scope(t_cmd *cmd, int scope);
int					is_nested_scope(t_executor *exec);
int					previous_cmd_connected_through_operation(t_executor *exec);
int					next_cmd_connected_through_operation(t_executor *exec);
int					arr_len(char **arr);
t_cmd				*previous_cmd_in_execution(t_executor *exec);
t_cmd				*next_cmd_in_execution(t_executor *exec);
int					get_nested_scope(t_executor *exec);
t_cmd				*final_cmd_in_scope(t_executor *exec, int scope);
int					get_scope(t_cmd *cmd);
int					get_outside_scope(t_cmd *cmd);
void				close_fd(t_fd_state *fd_state);
int					scope_length(t_executor *exec, int scope);
char				**argv(t_executor *exec);
char				**envp(t_executor *exec);

/*
 *   io_redirections
 */
t_fd_state			*last_output_redir(t_executor *exec);
t_fd_state			*last_input_redir(t_executor *exec);
t_fd_state			*here_document(t_executor *exec, const char *delimiter);
t_fd_state			*truncate_redirection(const char *file_name);
t_fd_state			*append_redirection(const char *file_name);
t_fd_state			*input_redirection(const char *file_name);

/*
 *   debugging
 */
void				print_exit_info(int status);
t_cmd				**mockup_three_cmds(t_env *env);
t_cmd				**mockup_single_cmd(t_env *env);
t_cmd				**mockup_empty_cmds(void);
t_cmd				**mockup_cmds_with_scopes(t_env *env);
t_cmd				*mockup_cmd(char **argv, t_oper operat, int *scope_stack,
						t_redir *redir, t_env *env);
char				**mockup_argv(char *cmd, char *arg1, char *arg2);
t_redir				*mockup_redir(t_red_sym redir_sym, char *redir_name,
						t_redir *next);
int					*mockup_scope_stack(int id_0, int id_1, int id_2);

#endif
