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

void	terminate(t_cmd2 *cmds, int status, char *msg)
{
	if (cmds)
        free_cmds(cmds);
	if (msg)
	{
		ft_putendl_fd(msg, STDERR_FILENO);
	}
	exit(status);
}



int	is_builtin(t_cmd2 *cmd)
{
	const char	*name;

    cmd_check(cmd);
	name = cmd->execution->argv[0];
	if (ft_strncmp(name, "cd", ft_strlen(name) + 1) == 0 || ft_strncmp(name,
			"echo", ft_strlen(name) + 1) == 0 || ft_strncmp(name, "env",
			ft_strlen(name) + 1) == 0 || ft_strncmp(name, "exit",
			ft_strlen(name) + 1) == 0 || ft_strncmp(name, "export",
			ft_strlen(name) + 1) == 0 || ft_strncmp(name, "pwd", ft_strlen(name)
			+ 1) == 0 || ft_strncmp(name, "unset", ft_strlen(name) + 1) == 0)
		return (1);
	return (0);
}
