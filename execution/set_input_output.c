/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:46 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/27 17:51:49 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	handle_pipe_output(t_cmd2 *cmd)
{
	t_pipe	*pipe;

	cmd_check(cmd);
	pipe = create_pipe();
	if (!pipe)
		terminate(cmd, EXIT_FAILURE, "minishell: failed to create pipe");
	cmd->execution->pipe = pipe;
}

void	handle_redir_input(t_cmd2 *cmd)
{
	t_fd_state	*input_fd;

	cmd_check(cmd);
	input_fd = last_input_redir(cmd);
	if (input_fd)
	{
		if (g_signal != SIGINT)
		{
			if (dup2(input_fd->fd, STDIN_FILENO) == -1)
				terminate(cmd, EXIT_FAILURE,
					"minishell: failed dup2 for input redirection");
		}
		if (input_fd->fd != STDIN_FILENO)
			close_redir(input_fd);
	}
}

void	handle_redir_output(t_cmd2 *cmd)
{
	t_fd_state	*output_fd;

	cmd_check(cmd);
	output_fd = last_output_redir(cmd);
	if (output_fd)
	{
		if (dup2(output_fd->fd, STDOUT_FILENO) == -1)
			terminate(cmd, EXIT_FAILURE,
				"minishell: dup2 for output redirection failed");
		if (output_fd->fd != STDOUT_FILENO)
			close_redir(output_fd);
	}
}

void	set_input_output(t_cmd2 *cmd)
{
	t_cmd2	*prev;
	t_cmd2	*next;

	cmd_check(cmd);
	if (cmd->execution->redirections)
	{
		handle_redir_input(cmd);
		handle_redir_output(cmd);
	}
	next = get_next_cmd(cmd);
	if (next && cmd->execution->operation == PIPE_)
		handle_pipe_output(cmd);
}
