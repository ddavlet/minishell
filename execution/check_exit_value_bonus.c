#include "execution.h"

static int	logic_operation_in_execution(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	if (previous_cmd_connected_through_operation(exec)
		&& (previous_cmd_in_execution(exec)->operat == AND
			|| previous_cmd_in_execution(exec)->operat == OR))
		return (1);
	else if (next_cmd_connected_through_operation(exec)
		&& (next_cmd_in_execution(exec)->operat == AND
			|| next_cmd_in_execution(exec)->operat == OR))
		return (1);
	return (0);
}

int	check_exit_value(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	close_fd(scope->pipe->write);
	if (next_cmd_in_execution(exec) == NULL)
		waitpid(scope->pid, &(exec->status), 0);
	else if (logic_operation_in_execution(exec, scope))
	{
		waitpid(scope->pid, &(exec->status), 0);
		evaluate_and_or(exec);
	}
	return (0);
}
