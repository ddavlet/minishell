/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:22 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 16:40:08 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int			set_input_output(t_cmd2 *cmd);
int			execute_command(t_cmd2 *cmd);
void		builtin_router(t_cmd2 *cmd);
int			wait_check(t_cmd2 *cmd);
int			evaluate_logic_operation(t_cmd2 *cmd);
t_fd_state	*initialize_fd_state(int fd);
int			is_logic_operation(t_cmd2 *cmd);
int			execute_cmd(t_cmd2 *cmd);
char		*build_path_from_env(char *name, t_env *env);
int			find_input_redirection(t_cmd2 *cmd);
int			find_output_redirection(t_cmd2 *cmd);

/*
 *   pipes
 */
t_pipe		*create_pipe(void);
void		close_redir(t_fd_state *input_fd_state);

/*
 *	utils
 */
t_cmd2		*get_next_cmd(t_cmd2 *cmd);
t_cmd2		*get_previous_cmd(t_cmd2 *cmd);
void		exit_handler(int status);
void		*msg_error(char *err);
void		free_arr2d(void **arr2d);
void		terminate(t_cmd2 *cmd, int status, char *msg);
int			is_builtin(t_cmd2 *cmd);
void		cmd_check(t_cmd2 *cmd);
int			is_piped(t_cmd2 *cmd);
void		update_exit_status(int exit_status, t_env *shell_env);
void		terminate_shell(t_env *shell_env, int exit_status, char *msg);

/*
 *   io_redirections
 */
t_fd_state	*last_output_redir(t_cmd2 *cmd);
t_fd_state	*last_input_redir(t_cmd2 *cmd);
t_pipe		*here_document(const char *delimiter, t_env *shell_env);
t_fd_state	*truncate_redirection(const char *file_name);
t_fd_state	*append_redirection(const char *file_name);
t_fd_state	*input_redirection(const char *file_name);
int			handle_redir_input(t_cmd2 *cmd);
int			handle_redir_output(t_cmd2 *cmd);
void		handle_heredoc_before_execution(t_cmd2 *cmds, t_env *shell_env);

extern int	g_signal;

#endif
