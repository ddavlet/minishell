#ifndef EXECUTION_H
# define EXECUTION_H

# include "../builtin/builtin.h"
# include "../libft/libft.h"
# include "../parsing/parsing.h"
# include <readline/readline.h>
# include <sys/wait.h>

# define SCOPE 1

typedef struct s_fd_state	t_fd_state;
typedef struct s_pipe		t_pipe;

typedef struct s_pipe
{
	int						*pipe_fd;
	t_fd_state				*read;
	t_fd_state				*write;
}							t_pipe;

typedef struct s_fd_state
{
	int						fd;
	int						is_open;
	t_pipe					*pipe;
}							t_fd_state;

typedef struct s_executor
{
	int						command_index;
	int						size;
	int						*status_codes;
	char					**envp;
	pid_t					*pids;
	t_cmd					**cmds;
	t_pipe					**pipes;
}							t_executor;

int							execution(t_cmd **cmds, char **envp);
void						set_io_streams(t_executor *exec);
int							execute(char **argv, char **envp);
void						execute_builtin(t_executor *exec);
int							check_exit_value(t_executor *exec);
void						evaluate_logic_operator(t_executor *exec);
t_fd_state					*initialize_fd_state(int fd);
int							is_logic(t_executor *exec);
char						**reverse_pars(t_cmd **cmds_tojoin, int commands);
void						initialize_status_codes(t_executor *exec);
void						initialize_pids(t_executor *exec);
void						initialize_execution_size(t_executor *exec);

/*
 *   pipes
 */
t_pipe						**initialize_pipes(t_executor *exec);
t_pipe						*create_pipe(void);
// void						close_pipe(t_pipe *pipe);
void						close_next_pipe(t_executor *exec);
t_pipe						*get_next_pipe(t_executor *exec);

/*
 *	utils
 */
t_cmd						*current_cmd(t_executor *exec);
t_cmd						*next_cmd(t_executor *exec, t_cmd *cmd);
t_cmd						*previous_cmd(t_executor *exec, t_cmd *cmd);
int							connected_through_operation(t_cmd *cmd,
								t_cmd *other);
int							is_final(t_executor *exec);
int							count_pipes(t_executor *exec,
								bool include_nested_scopes);
void						skip_nested_cmds(t_executor *exec);
void						exit_handler(int status);
char						*get_path(char *cmd, char *envp[]);
void						msg_error(char *err);
void						free_arr2d(void **arr2d);
void						terminate(t_executor *exec, int status, char *msg);
char						*get_name(char *cmd_path);
int							is_builtin(t_executor *exec);
int							is_inside_scope(t_cmd *cmd, int scope);
int							has_nested_scope(t_cmd *cmd);
int							arr_len(char **arr);
int							get_nested_scope(t_cmd *cmd);
t_cmd						*first_cmd_in_scope(t_executor *exec, int scope);
t_cmd						*final_cmd_in_scope(t_executor *exec, int scope);
int							get_scope(t_cmd *cmd);
void						close_fd(t_fd_state *fd_state);
int							scope_length(t_executor *exec, t_cmd *cmd,
								int scope);
t_pipe						*next_pipe(t_pipe **pipes);
t_pipe						*last_pipe(t_pipe **pipes);

/*
 *   io_redirections
 */
t_fd_state					*last_output_redir(t_executor *exec);
t_fd_state					*last_input_redir(t_executor *exec);
t_fd_state					*here_document(t_executor *exec,
								const char *delimiter);
t_fd_state					*truncate_redirection(const char *file_name);
t_fd_state					*append_redirection(const char *file_name);
t_fd_state					*input_redirection(const char *file_name);

/*
 *   debug
 */
void						debug_close_fd(t_fd_state *fd_state);
void						debug_pipe_information(t_pipe *pipe);
void						debug_started(char *msg);
void						debug_ended(char *msg);
void						debug_cmd_info(t_executor *exec);
void						debug_print_exit_code(t_executor *exec);

#endif
