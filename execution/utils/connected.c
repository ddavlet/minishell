 #include "../execution.h"

int	connected_through_operation(t_cmd *cmd, t_cmd *other)
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
