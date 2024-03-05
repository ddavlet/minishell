#include "execution.h"

// if (scope->oper_after == AND && exec->status != 0)
// 	terminate(NULL, NULL, EXIT_FAILURE);
// if (scope->oper_after == OR && exec->status == 0)
// 	terminate(NULL, NULL, EXIT_FAILURE);
void	check_logic(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE);
}

int connected_through_operation(t_cmd *cmd, t_cmd *other)
{
    int i;

    if (!cmd || !other)
        return (0);
    i = 0;
    // while (cmd->scope_stack[i] == other->scope_stack[i])
    //     i++;
    // if ()
}

int	is_logic_operation(t_executor *exec, t_scope *scope)
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
	else if (is_logic_operation(exec, scope))
	{
		waitpid(scope->pid, &(exec->status), 0);
		check_logic(exec, scope);
	}
	return (0);
}