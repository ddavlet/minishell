#include "../execution.h"

static int	connected_through_operation(t_cmd *cmd, t_cmd *other)
{
	int	last_common_scope;
	int	cmd_scope;
	int	other_scope;

	if (!cmd || !other)
		return (0);
	last_common_scope = 0;
	while (cmd->scope_stack[last_common_scope]
		&& other->scope_stack[last_common_scope]
		&& cmd->scope_stack[last_common_scope] == other->scope_stack[last_common_scope])
		last_common_scope++;
	cmd_scope = get_scope(cmd);
	other_scope = get_scope(other);
	if ((cmd_scope - last_common_scope < 2
			&& other_scope == last_common_scope) || (other_scope
			- last_common_scope < 2 && cmd_scope == last_common_scope))
		return (1);
	return (0);
}

int	previous_cmd_connected_through_operation(t_executor *exec)
{
	t_cmd	*cmd;
	t_cmd	*prev;

	cmd = current_cmd_in_execution(exec);
	prev = previous_cmd_in_execution(exec);
	return (connected_through_operation(cmd, prev));
}

int	next_cmd_connected_through_operation(t_executor *exec)
{
	t_cmd *cmd;
	t_cmd *next;

	cmd = current_cmd_in_execution(exec);
	next = next_cmd_in_execution(exec);
	return (connected_through_operation(cmd, next));
}