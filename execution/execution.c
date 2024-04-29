/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:19 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/29 17:06:25 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	reset_input_output(int stdin, int stdout)
{
	if (dup2(stdin, STDIN_FILENO) == -1)
		ft_putendl_fd("minishell: failed to reset stdin", STDERR_FILENO);
	if (dup2(stdout, STDOUT_FILENO) == -1)
		ft_putendl_fd("minishell: failed to reset stdout", STDERR_FILENO);
}

int	handle_previous_pipe(t_cmd2 *cmd)
{
	if (get_previous_cmd(cmd) && get_previous_cmd(cmd)->execution->pipe)
	{
		close_fd(get_previous_cmd(cmd)->execution->pipe->read);
		close_fd(get_previous_cmd(cmd)->execution->pipe->write);
	}
	return (1);
}

void	execute(t_cmd2 *cmd)
{
	if (is_builtin(cmd) && !is_piped(cmd))
		builtin_router(cmd);
	else
	{
		execute_cmd(cmd);
		// handle_previous_pipe(cmd);
		return ;
	}
}

void	execution_loop(t_cmd2 *cmds, int stdin, int stdout)
{
	t_cmd2	*cmd;

	cmd = cmds;
	while (cmd)
	{
		if (set_input_output(cmd))
		{
			append_envp(cmd->execution->shell_env, "LAST_EXIT_STATUS", "1");
			handle_previous_pipe(cmd);
			cmd = cmd->next;
			continue ;
		}
		expand_variables(cmd, cmd->execution->shell_env);
		process_quotations(cmds, cmd->execution->shell_env);
		if (g_signal == SIGINT)
			break ;
		if (cmd->execution->argv[0])
			execute(cmd);
		else
			cmd->execution->exit_status = EXIT_SUCCESS;
		handle_previous_pipe(cmd);
		if (!cmd->next || is_logic_operation(cmd))
			if (wait_check(cmd))
				break ;
		reset_input_output(stdin, stdout);
		cmd = cmd->next;
	}
	while (waitpid(-1, NULL, 0) != -1)
		;
	reset_input_output(stdin, stdout);
}

void	execution(t_cmd2 *cmds)
{
	int	stdin;
	int	stdout;

	if (!cmds)
		return ;
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	configure_signals_execution();
	handle_heredoc_before_execution(cmds, cmds->execution->shell_env);
	execution_loop(cmds, stdin, stdout);
	free_cmds(cmds);
}
