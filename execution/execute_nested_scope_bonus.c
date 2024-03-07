#include "execution.h"

int	execute_nested_scope(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "param check");
	scope->pid = fork();
	if (scope->pid == -1)
		terminate(NULL, NULL, EXIT_FAILURE, NULL);
	else if (scope->pid == 0)
	{
		scope = create_nested_scope(exec, scope);
		exit(shell(exec, scope));
	}
	else
		check_exit_value(exec, scope);
	return (0);
}

// ft_printf("DEBUG:loop.c: pipe_fd[0]: %d\n", exec->pipe_fd[0]);
// ft_printf("DEBUG:loop.c: pipe_fd[1]: %d\n", exec->pipe_fd[1]);