/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_codes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:27 by vketteni          #+#    #+#             */
/*   Updated: 2024/05/01 15:07:36 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	exit_code(int exit_status)
{
	if (WEXITSTATUS(exit_status))
		return (WEXITSTATUS(exit_status));
	if (WTERMSIG(exit_status))
		return (WTERMSIG(exit_status) + 128);
	return (0);
}

void	update_exit_status(int exit_status, t_env *shell_env)
{
	char	*tmp;

	tmp = ft_itoa(exit_status);
	append_envp(shell_env, "LAST_EXIT_STATUS", tmp);
	free(tmp);
}

void	wait_until(t_cmd2 *cmd)
{
	t_cmd2	*last;
	int		exit_status;
	pid_t	pid;

	cmd_check(cmd);
	last = cmd->cmds;
	while (last && last->execution->exit_status == EXIT_SUCCESS)
		last = last->next;
	while (last != cmd->next)
	{
		pid = last->execution->pid;
		if (waitpid(pid, &exit_status, 0) != -1)
		{
			last->execution->exit_status = exit_code(exit_status);
			update_exit_status(last->execution->exit_status,
				cmd->execution->shell_env);
		}
		last = last->next;
	}
}

int	wait_check(t_cmd2 *cmd)
{
	cmd_check(cmd);
	if (cmd->next == NULL)
		wait_until(cmd);
	else if (is_logic_operation(cmd))
	{
		wait_until(cmd);
		if (evaluate_logic_operation(cmd))
			return (1);
	}
	return (0);
}
