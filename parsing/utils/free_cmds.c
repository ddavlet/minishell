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
			free_pipe(execution->pipe);
		if (execution->heredoc)
			free_pipe(execution->heredoc);
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
