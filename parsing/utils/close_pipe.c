/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:31:36 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/25 08:42:57 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	close_pipe(t_pipe *pipe)
{
	if (pipe)
	{
		if (pipe->read->is_open)
			close_fd(pipe->read);
		if (pipe->write->is_open)
			close_fd(pipe->write);
	}
}

void	close_pipes(t_cmd2 *cmd)
{
	cmd = cmd->cmds;
	while (cmd)
	{
		if (cmd->execution && cmd->execution->pipe)
			close_pipe(cmd->execution->pipe);
		if (cmd->execution && cmd->execution->heredoc)
			close_pipe(cmd->execution->heredoc);
		cmd = cmd->next;
	}
}
