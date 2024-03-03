#include "execution.h"

int	execute_builtin(t_executor *exec, t_context *context)
{
	char	*path;
	char	**argv;
	char	**envp;

    (void)context;
	// Test if it actually executes on main envp;
	argv = exec->cmds[exec->command_index]->argv;
	envp = exec->cmds[exec->command_index]->env->envp;
	path = get_path(argv[0], envp);
	if (path == NULL)
    {
        free(path);
        ft_putstr_fd("pipex: execve", 2);
        ft_putendl_fd(argv[0], 2);
        return (-1);
    }
	if (execve(path, argv, envp) == -1)
    {
        ft_putstr_fd("pipex: command not found: ", 2);
        ft_putendl_fd(argv[0], 2);
        return (-1);
    }
	return (0);
}