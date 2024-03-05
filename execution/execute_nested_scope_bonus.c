#include "execution.h"

int	check_exit_value(t_executor *exec, t_scope *scope)
{
	if ((scope->scope_id != 1 && execution_is_last_in_logical_segment(exec))
		|| next_cmd_in_execution(exec) == NULL)
	{
		waitpid(scope->pid, &(exec->status), 0);
		if (scope->oper_after == AND && exec->status != 0)
			terminate(NULL, NULL, EXIT_FAILURE);
		if (scope->oper_after == OR && exec->status == 0)
			terminate(NULL, NULL, EXIT_FAILURE);
	}
	return (0);
}

int	execute_nested_scope(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE);
	scope->pid = fork();
	if (scope->pid == -1)
		terminate(NULL, NULL, EXIT_FAILURE);
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