#ifndef EXECUTION_H
# define EXECUTION_H

# include "../builtin/builtin.h"
# include "../libft/libft.h"
# include "../parsing/parsing.h"
# include <readline/readline.h>
# include <sys/wait.h>

# define HAS_NOT_RUN -1

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
	int						stdin;
	int						stdout;
	int						*exit_codes;
	char					**envp;
	pid_t					*pids;
	t_cmd					**cmds;
	t_pipe					**pipes;
}							t_executor;

int							execution(t_cmd **cmds, char **envp);
void						set_input_output(t_executor *exec);
int							child_process(t_executor *exec);
void						execute_builtin(t_executor *exec);
int							wait_check(t_executor *exec);
void						evaluate_logic_operator(t_executor *exec);
t_fd_state					*initialize_fd_state(int fd);
int							is_logic(t_executor *exec);
char						**reverse_pars(t_cmd **cmds_tojoin, int commands);
void						initialize_exit_codes(t_executor *exec);
void						initialize_pids(t_executor *exec);
void						execute_cmd(t_executor *exec);
char						*build_path_from_env(char *name);

/*
 *   pipes
 */
t_pipe						**initialize_pipes(t_executor *exec);
t_pipe						*create_pipe(void);
void						close_next_pipe(t_executor *exec);
t_pipe						*get_next_pipe(t_executor *exec);

/*
 *	utils
 */
t_cmd						*get_current_cmd(t_executor *exec);
t_cmd						*get_next_cmd(t_executor *exec, t_cmd *cmd);
t_cmd						*get_previous_cmd(t_executor *exec, t_cmd *cmd);
int							is_final(t_executor *exec);
int							count_pipes(t_executor *exec);
void						exit_handler(int status);
void						msg_error(char *err);
void						free_arr2d(void **arr2d);
void						terminate(t_executor *exec, int status, char *msg);
int							is_builtin(t_cmd *cmd);
int							arr_len(char **arr);
void						close_fd(t_executor *exec, t_fd_state *fd_state);
t_pipe						*next_pipe(t_pipe **pipes);
t_pipe						*last_pipe(t_pipe **pipes);
pid_t						get_pid(t_executor *exec, int command_index);
void						set_pid(t_executor *exec, int command_index,
								pid_t pid);
int							get_execution_length(t_executor *exec);
int							get_exit_code(t_executor *exec, int command_index);
void						set_exit_code(t_executor *exec, int command_index,
								int exit_code);
void						cmds_check(t_cmd **cmds);
void						reset_input_output(t_executor *exec);

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
void						handle_redir_input(t_executor *exec);
void						handle_redir_output(t_executor *exec);

/*
 *   debug
 */
// void						debug_close_fd(t_fd_state *fd_state);
// void						debug_pipe_information(t_pipe *pipe);
// void						debug_started(char *msg);
// void						debug_ended(char *msg);
// void						debug_cmd_info(t_executor *exec);
// void						debug_print_exit_code(t_executor *exec);

#endif
