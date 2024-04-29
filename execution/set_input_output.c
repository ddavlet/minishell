/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:46 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 16:40:31 by ddavlety         ###   ########.fr       */
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

int	handle_redir_input(t_cmd2 *cmd)
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
		return (0);
	}
	else
		return (1);

}

int	handle_redir_output(t_cmd2 *cmd)
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
		return (0);
	}
	else
		return (1);
}

int	find_input_redirection(t_cmd2 *cmd)
{
	t_redir	*redir;

	redir = cmd->execution->redirections;
	while (redir)
	{
		if (redir->redir_sym == RED_INP || redir->redir_sym == HERE_DOC)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	find_output_redirection(t_cmd2 *cmd)
{
	t_redir	*redir;

	redir = cmd->execution->redirections;
	while (redir)
	{
		if (redir->redir_sym == RED_OUT || redir->redir_sym == APP_OUT)
			return (1);
		redir = redir->next;
	}
	return (0);
}

int	set_input_output(t_cmd2 *cmd)
{
	t_cmd2	*next;

	cmd_check(cmd);
	if (cmd->execution->redirections)
	{
		// if (find_input_redirection(cmd))
			if (handle_redir_input(cmd))
				return (1);
		// if (find_output_redirection(cmd))
			if (handle_redir_output(cmd))
				return (1);
	}
	next = get_next_cmd(cmd);
	if (next && cmd->execution->operation == PIPE_)
		handle_pipe_output(cmd);
	return (0);
}
