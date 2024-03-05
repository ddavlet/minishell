#include "execution.h"

int	connected_through_operation(t_cmd *comparison, t_cmd *other)
{
	int	last_common_scope;
	int	actual_scope;

	if (!comparison || !other)
		return (0);
	last_common_scope = 0;
	while (comparison->scope_stack[last_common_scope] == other->scope_stack[last_common_scope])
		last_common_scope++;
	while (comparison->scope_stack[actual_scope])
		actual_scope++;
	if (last_common_scope - actual_scope > 1)
		return (0);
	return (1);
}

int	is_first_operant(exec)
{
	t_cmd	*executed_cmd;
	t_cmd	*next_cmd;

	executed_cmd = current_cmd_in_execution(exec);
	next_cmd = last_cmd_in_execution(exec);
	if (connected_through_operation(executed_cmd, next_cmd)
		&& (next_cmd->operat == AND || next_cmd->operat == OR))
		return (1);
	return (0);
}

int	is_second_operant(exec)
{
	t_cmd	*executed_cmd;
	t_cmd	*previous_cmd;

	executed_cmd = current_cmd_in_execution(exec);
	previous_cmd = last_cmd_in_execution(exec);
	if (connected_through_operation(executed_cmd, previous_cmd)
		&& (previous_cmd->operat == AND || previous_cmd->operat == OR))
		return (1);
	return (0);
}

void	evaluate_logic_operation(t_executor *exec)
{
	t_cmd	*executed_cmd;
	t_cmd	*previous_cmd;
	t_cmd	*next_cmd;

	if (!exec || !exec->cmds)
		terminate(NULL, NULL, EXIT_FAILURE);
	executed_cmd = current_cmd_in_execution(exec);
	next_cmd = next_cmd_in_execution(exec);
	previous_cmd = last_cmd_in_execution(exec);
	if (is_first_operant(exec))
        evaluate_as_first_operant(exec);
        // if (executed_cmd->operat == OR
        // 	&& exec->status[exec->command_index] == EXIT_SUCCESS)
        // 	terminate(NULL, NULL, EXIT_FAILURE);
        // if (executed_cmd->operat == AND && exec->status == EXIT_FAILURE)
        // 	terminate(NULL, NULL, EXIT_FAILURE);
    if	(is_second_operant(exec))
        evaluate_as_second_operant(exec)
    // {
    //     if (previous_cmd->operat == AND && exec->status == EXIT_FAILURE)
    //         terminate(NULL, NULL, EXIT_FAILURE);
    //     if (previous_cmd->operat == OR && exec->status == EXIT_FAILURE)
    //         terminate(NULL, NULL, EXIT_FAILURE);
    // }
}

int	execution_has_logic_operation(t_executor *exec, t_scope *scope)
{
	t_cmd	*prev;
	t_cmd	*next;
	t_cmd	*cmd;

	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE);
	prev = previous_cmd_in_execution(exec);
	next = next_cmd_in_execution(exec);
	cmd = current_cmd_in_execution(exec);
	if (!prev || !next)
		terminate(NULL, NULL, EXIT_FAILURE);
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
		terminate(NULL, NULL, EXIT_FAILURE);
	if (next_cmd_in_execution(exec) == NULL)
		waitpid(scope->pid, &(exec->status), 0);
	else if (execution_has_logic_operation(exec, scope))
	{
		waitpid(scope->pid, &(exec->status), 0);
		evaluate_logic_operation(exec, scope);
	}
	return (0);
}