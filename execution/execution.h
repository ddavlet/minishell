#ifndef EXECUTION_H
# define EXECUTION_H

# include "../builtin/builtin.h"
# include "../libft/libft.h"
# include "../parsing/parsing.h"
# include "../parsing_experimental/parsing2.h"
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

void	execution(t_cmd2 *cmds);
void						set_input_output(t_cmd2 *cmd);
int							child_process(t_cmd2 *cmd);
int							builtin_router(t_cmd2 *cmd);
int							wait_check(t_cmd2 *cmd);
void						evaluate_logic_operation(t_cmd2 *cmd);
t_fd_state					*initialize_fd_state(int fd);
int							is_logic_operation(t_cmd2 *cmd);
// char						**reverse_pars(t_cmd2 **cmds_tojoin, int commands);
void						initialize_exit_codes(t_cmd2 *cmd);
void						initialize_pids(t_cmd2 *cmd);
int							execute_cmd(t_cmd2 *cmd);
char						*build_path_from_env(char *name, t_env *env);

/*
 *   pipes
 */
t_pipe						**initialize_pipes(t_cmd2 *cmd);
t_pipe						*create_pipe(void);
void						close_next_pipe(t_cmd2 *cmd);
t_pipe						*get_next_pipe(t_cmd2 *cmd);

/*
 *	utils
 */
t_cmd2						*get_next_cmd(t_cmd2 *cmd);
t_cmd2						*get_previous_cmd(t_cmd2 *cmd);
int							count_pipes(t_cmd2 *cmd);
void						exit_handler(int status);
void						msg_error(char *err);
void						free_arr2d(void **arr2d);
void						terminate(t_cmd2 *cmd, int status, char *msg);
int							is_builtin(t_cmd2 *cmd);
int							arr_len(char **arr);
void						close_fd(t_fd_state *fd_state);
t_pipe						*next_pipe(t_pipe **pipes);
t_pipe						*last_pipe(t_pipe **pipes);
pid_t						get_pid(t_cmd2 *cmd, int command_index);
void						set_pid(t_cmd2 *cmd, int command_index, pid_t pid);
int							get_execution_length(t_cmd2 *cmd);
int							get_exit_code(t_cmd2 *cmd, int command_index);
void						set_exit_code(t_cmd2 *cmd, int command_index,
								int exit_code);
void						cmds_check(t_cmd2 *cmds);
void						reset_input_output(t_cmd2 *cmd);
void						free_execution(t_cmd2 *cmd);
void						cmd_check(t_cmd2 *cmd);

/*
 *   io_redirections
 */
t_fd_state					*last_output_redir(t_cmd2 *cmd);
t_fd_state					*last_input_redir(t_cmd2 *cmd);
t_fd_state					*here_document(const char *delimiter, t_env *env);
t_fd_state					*truncate_redirection(const char *file_name);
t_fd_state					*append_redirection(const char *file_name);
t_fd_state					*input_redirection(const char *file_name);
void						handle_redir_input(t_cmd2 *cmd);
void						handle_redir_output(t_cmd2 *cmd);

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
