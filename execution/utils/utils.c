#include "../execution.h"

void	free_arr2d(void **arr2d)
{
	int		i;
	char	**arr;

	arr = (char **)arr2d;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	msg_error(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
};
void	exit_handler(int status)
{
	if (status == 0)
		exit(0);
	else
		exit(status);
}

void	free_execution(t_executor *exec)
{
	int	i;

	free(exec->exit_codes);
	free(exec->pids);
	i = 0;
	while (exec->pipes[i])
	{
		if (exec->pipes[i]->write->is_open)
			close_fd(exec, exec->pipes[i]->write);
		if (exec->pipes[i]->read->is_open)
			close_fd(exec, exec->pipes[i]->read);
		free(exec->pipes[i]->read);
		free(exec->pipes[i]->write);
		free(exec->pipes[i]);
	}
	free(exec->pipes);
	free(exec);
}

void	terminate(t_cmd2 *cmd, int status, char *msg)
{
	int	i;

	if (exec)
	{
		free(exec->exit_codes);
		free(exec->pids);
		i = 0;
		if (exec->pipes)
		{
			while (exec->pipes[i])
			{
				if (exec->pipes[i]->write->is_open)
					close_fd(exec, exec->pipes[i]->write);
				if (exec->pipes[i]->read->is_open)
					close_fd(exec, exec->pipes[i]->read);
				free(exec->pipes[i]->read);
				free(exec->pipes[i]->write);
				free(exec->pipes[i]);
			}
		}
		free(exec->pipes);
		terminate_commands(exec->cmds);
		free(exec);
	}
	if (msg)
	{
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	exit(status);
}

void	close_fd(t_fd_state *fd_state)
{
	if (!fd_state)
    {
        ft_putendl_fd("can't close file descriptor, missing state", STDERR_FILENO);
		return ;
    }
	// debug_close_fd(fd_state);
	if (fd_state->is_open == 0)
        ft_putendl_fd("file descriptor already closed", STDERR_FILENO);
	else if (close(fd_state->fd) == -1)
        ft_putendl_fd("failed to close file descriptor", STDERR_FILENO);
	fd_state->is_open = 0;
}

int	count_pipes(t_executor *exec)
{
	t_cmd	*cmd;
	int		count;

	count = 0;
	cmd = exec->cmds[0];
	while (cmd)
	{
		if (cmd->operat == PIPE)
			count++;
		cmd = get_next_cmd(exec, cmd);
	}
	return (count);
}

t_pipe	*next_pipe(t_pipe **pipes)
{
	int	i;

	i = 0;
	while (pipes[i]->write->is_open == 0)
		i++;
	return (pipes[i]);
}

t_pipe	*last_pipe(t_pipe **pipes)
{
	int	i;

	i = 0;
	while (pipes[i] && pipes[i]->write->is_open == 0)
		i++;
	return (pipes[i - 1]);
}

int	get_execution_length(t_executor *exec)
{
	int		len;
	t_cmd	**cmds;

	if (!exec || !exec->cmds)
		terminate(exec, EXIT_FAILURE, "couldn't get execution length");
	cmds = exec->cmds;
	len = 0;
	while (cmds[len])
		len++;
	return (len);
}

int	is_builtin(t_cmd *cmd)
{
	char	*name;

	name = cmd->argv[0];
	if (ft_strncmp(name, "cd", ft_strlen(name) + 1) == 0 || ft_strncmp(name,
			"echo", ft_strlen(name) + 1) == 0 || ft_strncmp(name, "env",
			ft_strlen(name) + 1) == 0 || ft_strncmp(name, "exit",
			ft_strlen(name) + 1) == 0 || ft_strncmp(name, "export",
			ft_strlen(name) + 1) == 0 || ft_strncmp(name, "pwd", ft_strlen(name)
			+ 1) == 0 || ft_strncmp(name, "unset", ft_strlen(name) + 1) == 0)
		return (1);
	return (0);
}
