#include "execution.h"

static int	is_part_of_logic_operation(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	if (previous_cmd_connected_through_operation(exec)
		&& (previous_cmd_in_execution(exec)->operat == AND
			|| previous_cmd_in_execution(exec)->operat == OR))
		return (1);
	else if (next_cmd_connected_through_operation(exec)
		&& (current_cmd_in_execution(exec)->operat == AND
			|| current_cmd_in_execution(exec)->operat == OR))
		return (1);
	return (0);
}

int	check_exit_value(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	if (scope->pipe && current_cmd_in_execution(exec) != NULL)
		close_fd(scope->pipe->write, exec);
	if (is_part_of_logic_operation(exec, scope))
	{
		waitpid(scope->pid, &(exec->status), 0);
		evaluate_and_or(exec);
	}
	else if (current_cmd_in_execution(exec) == final_cmd_in_scope(exec, scope))
		waitpid(scope->pid, &(exec->status), 0);
	return (0);
}
