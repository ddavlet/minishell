#include "execution.h"

static int	execution_has_logic_operation(t_executor *exec, t_scope *scope)
{
	t_cmd	*prev;
	t_cmd	*next;
	t_cmd	*cmd;

	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "param check");
	prev = previous_cmd_in_execution(exec);
	next = next_cmd_in_execution(exec);
	cmd = current_cmd_in_execution(exec);
	if (connected_through_operation(cmd, prev) && (prev->operat == AND
			|| prev->operat == OR))
		return (1);
	else if (connected_through_operation(cmd, next) && (next->operat == AND
			|| next->operat == OR))
		return (1);
	return (0);
}

int	check_exit_value(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "param check");
	if (next_cmd_in_execution(exec) == NULL)
		waitpid(scope->pid, &(exec->status), 0);
	else if (execution_has_logic_operation(exec, scope))
	{
		waitpid(scope->pid, &(exec->status), 0);
		evaluate_and_or(exec);
	}
	return (0);
}
