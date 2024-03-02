#include "execution.h"

int	builtin_execution(t_executor *exec, t_context *context)
{
	char	*path;
	char	**argv;
	char	**envp;

	// Test if it actually executes on main envp;
	argv = exec->cmds[exec->command_index]->argv;
	argv = exec->cmds[exec->command_index]->env->envp;
	path = get_path(argv[0], envp);
	if (path == NULL)
		return (path_error(argv[0]));
	if (execve(path, argv, envp) == -1)
		return ((execve_error(path, argv[0])));
	return (0);
}