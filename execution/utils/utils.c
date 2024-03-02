#include "../execution.h"

void	free_arr2d(void **arr2d)
{
	int	i;
    char **arr;

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
}


unsigned long	rand_simple(void)
{
	static unsigned long	lcg_prev = 21512345435143;
	const unsigned long		a = 1103515245;
	const unsigned long		c = 12345;
	const unsigned long		m = 1UL << 31; // 2^31

	lcg_prev = (a * lcg_prev + c) % m;
	return (lcg_prev);
}

void	exit_handler(int status)
{
	if (status == 0)
		exit(0);
	else
		exit(status);
}

void	terminate(t_executor *exec, t_context *context, int status)
{
	// Finish this function
	// Free all the memory
	(void)exec;
	(void)context;
	exit_handler(status);
}

int	is_last(t_executor *exec)
{
	if (exec->cmds[exec->command_index + 1] == NULL)
		return (1);
	return (0);
}

int	has_finished(t_executor *exec)
{
	if (exec->cmds[exec->command_index] == NULL)
		return (1);
	return (0);
}

char	*get_name(char *cmd_path)
{
	char	*last;

	last = NULL;
	while (cmd_path)
	{
		last = cmd_path;
		cmd_path = ft_strchr(cmd_path, '/');
	}
	return (last);
}

int	is_builtin(t_executor *exec)
{
	char	*cmd;

	cmd = exec->cmds[exec->command_index]->com;
	if (ft_strchr(cmd, '/'))
	{
		cmd = get_name(cmd);
		if (!cmd)
			return (0);
	}
	if (ft_strncmp(cmd, "cd", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "echo", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "env", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "exit", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "export", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "pwd", ft_strlen(cmd) == 0)
		|| ft_strncmp(cmd, "unset", ft_strlen(cmd) == 0)
		)
		return (1);
	return (0);
}