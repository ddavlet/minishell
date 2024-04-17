#include "../execution.h"

void	terminate_shell(t_env *shell_env, int exit_status, char *msg)
{
	if (shell_env)
		free_env(shell_env);
	if (msg)
	{
		if (exit_status != 0)
			ft_putendl_fd(msg, STDERR_FILENO);
		else
			ft_putendl_fd(msg, STDOUT_FILENO);
	}
	exit(exit_status);
}
