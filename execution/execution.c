
#include "execution.h"

int	execute_command(t_cmd *cmd, char *envp[])
{
	char	*cmd_name;
	char	*path;

	cmd_name = cmd->com;
	if (cmd->argv == NULL)
	{
		terminate_execution((t_cmd **)NULL, envp);
		return (-1);
	}
	path = get_path(cmd_name, envp);
	if (path == NULL)
	{
		free(path);
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(cmd_name, 2);
		terminate_execution((t_cmd **)NULL, envp);
		return (-1);
	}
	if (execve(path, cmd->argv, envp) == -1)
	{
		free(path);
		ft_putstr_fd("pipex: execve", 2);
		ft_putendl_fd(cmd_name, 2);
		free_string_arr(cmd->argv);
		return (-1);
	}
	return (0);
}

int	initialize_executor(t_cmd **cmds, char *envp[])
{
	if (!cmds || !envp)
		return (NULL);
	executor = (t_executor *)malloc(sizeof(t_executor));
	if (!executor)
		return (NULL);
	executor->in_fd = 0;
	executor->out_fd = 1;
	executor->pipe_fd[0] = 0;
	executor->pipe_fd[1] = 0;
	executor->pid = 0;
	executor->status = 0;
	executor->cmds = cmds;
	executor->envp = envp;
	return (executor);
}

int	execute_command_line(t_cmd **cmds, char *envp[])
{
	t_executor	executor;

	executor = initialize_executor(cmds, envp);
	if (!executor)
		return (-1);
	if (!cmds || cmds[0] == NULL)
	{
		terminate_execution(executor);
		return (-1);
	}
	execute_loop(executor)
	terminate_execution(executor);
	return (0);
}
