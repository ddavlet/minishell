#ifndef EXECUTION_H
# define EXECUTION_H

# include "../builtin/builtin.h"
# include "../libft/libft.h"
# include "../parsing/parsing.h"
# include "../signal_handling/signals.h"
# include <readline/readline.h>
# include <stdio.h>
# include <sys/wait.h>

void		execution(t_cmd2 *cmds);
void		set_input_output(t_cmd2 *cmd);
int			execute_command(t_cmd2 *cmd);
void		builtin_router(t_cmd2 *cmd);
int			wait_check(t_cmd2 *cmd);
int			evaluate_logic_operation(t_cmd2 *cmd);
t_fd_state	*initialize_fd_state(int fd);
int			is_logic_operation(t_cmd2 *cmd);
void		execute_cmd(t_cmd2 *cmd);
char		*build_path_from_env(char *name, t_env *env);

extern int	g_signal;

/*
 *   pipes
 */
t_pipe		*create_pipe(void);
void	close_pipe(t_pipe *pipe);
void    close_redir(t_fd_state *input_fd_state);


/*
 *	utils
 */
t_cmd2		*get_next_cmd(t_cmd2 *cmd);
t_cmd2		*get_previous_cmd(t_cmd2 *cmd);
void		exit_handler(int status);
void		msg_error(char *err);
void		free_arr2d(void **arr2d);
int			terminate(t_cmd2 *cmd, int status, char *msg);
int			is_builtin(t_cmd2 *cmd);
void		cmd_check(t_cmd2 *cmd);
int			is_piped(t_cmd2 *cmd);
int			exit_code(int status);

/*
 *   io_redirections
 */
t_fd_state	*last_output_redir(t_cmd2 *cmd);
t_fd_state	*last_input_redir(t_cmd2 *cmd);
t_fd_state	*here_document(const char *delimiter, t_env *env);
t_fd_state	*truncate_redirection(const char *file_name);
t_fd_state	*append_redirection(const char *file_name);
t_fd_state	*input_redirection(const char *file_name);
void		handle_redir_input(t_cmd2 *cmd);
void		handle_redir_output(t_cmd2 *cmd);

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
