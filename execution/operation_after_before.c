#include "execution.h"

t_oper	operation_after(t_executor *exec, t_scope *scope)
{
	t_cmd	*last_cmd;
	t_cmd	*next_cmd;

	if (param_check(exec, scope))
		terminate(NULL, NULL, EXIT_FAILURE);
	last_cmd = last_cmd_in_scope(exec, scope);
	next_cmd = next_command(exec, last_cmd);
	if (next_cmd == NULL)
		return (RUN);
	else if (get_scope(last_cmd) == get_scope(next_cmd)
		|| get_outside_scope(last_cmd) == get_scope(next_cmd)
		|| get_outside_scope(last_cmd) == get_outside_scope(next_cmd))
		return (next_cmd->operat);
	else
		return (RUN);
}

t_oper	operation_before(t_executor *exec, t_scope *scope)
{
	t_cmd	*first_cmd_in_scope;
	t_cmd	*previous_cmd;

	if (param_check(exec, scope))
		terminate(NULL, NULL, EXIT_FAILURE);
	first_cmd_in_scope = current_cmd_in_execution(exec);
	previous_cmd = previous_cmd_in_execution(exec);
	if (exec->command_index == 0)
		return (RUN);
	else if (get_scope(first_cmd_in_scope) == get_scope(previous_cmd)
		|| get_outside_scope(first_cmd_in_scope) == get_scope(previous_cmd)
		|| get_outside_scope(first_cmd_in_scope) == get_outside_scope(previous_cmd))
		return (previous_cmd->operat);
	else
		return (RUN);
}
