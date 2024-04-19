/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:27 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 17:22:45 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	free_execution_data(t_execution *execution)
{
	if (execution)
	{
		if (execution->argv)
			free_argv(execution->argv);
		if (execution->pipe)
		{
			if (execution->pipe->write->is_open)
				close_fd(execution->pipe->write);
			if (execution->pipe->read->is_open)
				close_fd(execution->pipe->read);
			free(execution->pipe->read);
			free(execution->pipe->write);
			free(execution->pipe->pipe_fd);
			free(execution->pipe);
		}
		if (execution->redirections)
			free_redirections(execution->redirections);
		free(execution);
	}
}

void	free_cmds(t_cmd2 *cmds)
{
	t_cmd2	*tmp;
	t_cmd2	*cmd;

	cmd = cmds;
	while (cmd)
	{
		tmp = cmd->next;
		free_execution_data(cmd->execution);
		free(cmd);
		cmd = tmp;
	}
}
