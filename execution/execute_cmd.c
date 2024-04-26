/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:32:16 by vketteni          #+#    #+#             */
/*   Updated: 2024/04/26 13:23:45 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	execute_command(t_cmd2 *cmd)
{
	const char	*path;
	char *const	*argv;
	char *const	*envp;

	cmd_check(cmd);
	envp = cmd->execution->shell_env->envp;
	argv = (char *const *)cmd->execution->argv;
	if (ft_strchr(argv[0], '/') == NULL)
	{
		path = (const char *)build_path_from_env(argv[0],
				cmd->execution->shell_env);
		if (path == NULL)
			terminate(cmd, 127, "minishell: couldn't find path");
	}
	else
		path = argv[0];
	if (execve(path, argv, envp) == -1)
		terminate_shell(cmd->execution->shell_env, 126,
			"minishell: permission denied");
	return (0);
}

void	handle_pipes(t_cmd2 *cmd)
{
	if (get_previous_cmd(cmd) && get_previous_cmd(cmd)->execution->pipe)
	{
		close_fd(get_previous_cmd(cmd)->execution->pipe->write);
		if (dup2(get_previous_cmd(cmd)->execution->pipe->read->fd, STDIN_FILENO) == -1)
			terminate(cmd, EXIT_FAILURE,
				"minishell: dup2 for pipe input redirection failed");
		close_fd(get_previous_cmd(cmd)->execution->pipe->read);
	}
	if (cmd->execution->pipe)
	{
		close_fd(cmd->execution->pipe->read);
		if (dup2(cmd->execution->pipe->write->fd, STDOUT_FILENO) == -1)
			terminate(cmd, EXIT_FAILURE,
				"minishell: unable to set pipe to output");
		close_fd(cmd->execution->pipe->write);
	}
	close_pipes(cmd);
}

int	execute_cmd(t_cmd2 *cmd)
{
	pid_t	pid;

	cmd_check(cmd);
	pid = fork();
	cmd->execution->pid = pid;
	if (pid == -1)
		terminate(cmd, EXIT_FAILURE, "minishell: failed to fork");
	else if (pid == 0)
	{
		handle_pipes(cmd);
		if (is_builtin(cmd))
		{
			builtin_router(cmd);
			exit(cmd->execution->exit_status);
		}
		else
			return (execute_command(cmd));
	}
	return (0);
}
