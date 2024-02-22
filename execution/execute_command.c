#include "execution.h"

int execve_error(char *path, char *cmd_name)
{
    free(path);
    ft_putstr_fd("pipex: execve", 2);
    ft_putendl_fd(cmd_name, 2);
    return (-1);
}

int path_error(char *cmd_name)
{
    ft_putstr_fd("pipex: command not found: ", 2);
    ft_putendl_fd(cmd_name, 2);
    return (-1);
}

int	execute_command(const char *argv[], const char *envp[])
{
	const char	*path;

	path = get_path(argv[0], envp);
	if (path == NULL)
        return (path_error(argv[0]));
	if (execve(path, argv, envp) == -1)
        return ((execve_error(path)));
	return (0);
}
