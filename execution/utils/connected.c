#include "../execution.h"

static int	connected_through_operation(t_cmd *comparison, t_cmd *other)
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

int previous_cmd_connected_through_operation(t_executor *exec)
{
    t_cmd *cmd;
    t_cmd *prev;

    cmd = current_cmd_in_execution(exec);
    prev = previous_cmd_in_execution(exec);
    return (connected_through_operation(cmd, prev));
}

int next_cmd_connected_through_operation(t_executor *exec)
{
    t_cmd *cmd;
    t_cmd *next;

    cmd = current_cmd_in_execution(exec);
    next = next_cmd_in_execution(exec);
    return (connected_through_operation(cmd, next));
}