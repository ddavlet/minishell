/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:30:40 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 14:14:07 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_execution	*initialize_execution_data(void)
{
	t_execution	*execution;

	execution = (t_execution *)ft_calloc(1, sizeof(t_execution));
	if (!execution)
		return (NULL);
	execution->argv = NULL;
	execution->pipe = NULL;
	execution->heredoc = NULL;
	execution->redirections = NULL;
	execution->shell_env = NULL;
	execution->exit_status = EXIT_FAILURE;
	execution->operation = NONE;
	execution->pid = 0;
	return (execution);
}

t_cmd2	*initialize_command(void)
{
	t_cmd2		*cmd;
	t_execution	*execution;

	execution = initialize_execution_data();
	if (!execution)
		return (NULL);
	cmd = (t_cmd2 *)ft_calloc(1, sizeof(t_cmd2));
	if (!cmd)
	{
		free(execution);
		return (NULL);
	}
	cmd->execution = execution;
	cmd->cmds = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd2	*parse_command(t_token *start, t_token *end)
{
	t_cmd2	*cmd;

	cmd = initialize_command();
	if (!cmd)
		return (NULL);
	if (start->literal[0] == '(')
	{
		if (parse_nested_argv((char ***)&(cmd->execution->argv),
				start, end) == -1
			|| parse_operation(&(cmd->execution->operation), end) == -1)
		{
			free_cmds(cmd);
			return (NULL);
		}
	}
	else if (parse_redir(&(cmd->execution->redirections), start, end) == -1
		|| parse_argv((char ***)&(cmd->execution->argv), start, end) == -1
		|| parse_operation(&(cmd->execution->operation), end) == -1)
	{
		free_cmds(cmd);
		return (NULL);
	}
	return (cmd);
}
