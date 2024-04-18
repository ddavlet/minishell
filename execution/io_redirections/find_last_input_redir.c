/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_last_input_redir.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:30:09 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/18 13:43:21 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution.h"

int	is_input_redir(int fd, t_red_sym symbol)
{
	if (fd != STDIN_FILENO && (symbol == RED_INP || symbol == HEAR_DOC))
		return (1);
	return (0);
}

void	close_last_redir(t_redir *redir, t_fd_state *input_fd_state)
{
	if (input_fd_state && is_input_redir(input_fd_state->fd,
			redir->redir_sym))
	{
		if (input_fd_state->pipe)
			close_pipe(input_fd_state->pipe);
		else
			close_fd(input_fd_state);
	}
}

t_fd_state	*last_input_redir(t_cmd2 *cmd)
{
	t_redir		*redir;
	t_fd_state	*input_fd_state;
	t_env		*shell_env;

	cmd_check(cmd);
	redir = cmd->execution->redirections;
	if (!redir)
		return (NULL);
	shell_env = cmd->execution->shell_env;
	input_fd_state = NULL;
	while (redir)
	{
		if (redir->redir_sym == RED_INP)
			input_fd_state = input_redirection(redir->redir_name);
		else if (redir->redir_sym == HEAR_DOC)
			input_fd_state = here_document(redir->redir_name, shell_env);
		redir = redir->next;
		if (redir)
			close_last_redir(redir, input_fd_state);
	}
	return (input_fd_state);
}
