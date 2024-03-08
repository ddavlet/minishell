#include "execution.h"

static t_oper	operation_after(t_executor *exec, t_scope *scope)
{
	t_cmd	*final_cmd;
	t_cmd	*next;

	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	final_cmd = final_cmd_in_scope(exec, scope);
	next = next_cmd(exec, final_cmd);
	if (next == NULL)
		return (RUN);
	else if (get_outside_scope(final_cmd) == get_scope(next)
		|| get_outside_scope(final_cmd) == get_outside_scope(next))
		return (next->operat);
	else
		return (RUN);
}

static t_oper	operation_before(t_executor *exec, t_scope *scope)
{
	t_cmd	*first_cmd_in_scope;
	t_cmd	*previous_cmd;

	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	first_cmd_in_scope = current_cmd_in_execution(exec);
	previous_cmd = previous_cmd_in_execution(exec);
	if (exec->command_index == 0)
		return (RUN);
	else if (get_outside_scope(first_cmd_in_scope) == get_scope(previous_cmd)
		|| get_outside_scope(first_cmd_in_scope) == get_outside_scope(previous_cmd))
		return (previous_cmd->operat);
	else
		return (RUN);
}

static int	set_input_output(t_executor *exec, t_scope *subscope,
		t_scope *scope)
{
	if (!subscope || !scope)
		return (-1);
	if (operation_before(exec, subscope) == PIPE)
	{
		if (scope->pipe == NULL)
			return (-1);
		subscope->input_fd = scope->pipe->read;
	}
	else
		subscope->input_fd = scope->input_fd;
	if (operation_after(exec, subscope) == PIPE)
	{
		if (scope->pipe == NULL)
			return (-1);
		subscope->output_fd = scope->pipe->write;
	}
	else
		subscope->output_fd = scope->output_fd;
	return (0);
}

t_scope	*create_nested_scope(t_executor *exec, t_scope *scope)
{
	t_scope	*nested_scope;

	nested_scope = (t_scope *)ft_calloc(1, sizeof(t_scope));
	if (!nested_scope)
		return (NULL);
	nested_scope->scope_id = find_nested_id(exec, scope);
	if (!(nested_scope->scope_id))
		terminate(NULL, nested_scope, EXIT_FAILURE,
			"couldn't create nested scope");
	if (set_input_output(exec, nested_scope, scope) == -1)
		terminate(NULL, nested_scope, EXIT_FAILURE,
			"couldn't create nested scope");
	nested_scope->pid = -1;
	nested_scope->pipe = NULL;
	return (nested_scope);
}

t_scope	*initialize_scope(t_executor *exec)
{
	t_scope	*scope;

	scope = (t_scope *)ft_calloc(1, sizeof(t_scope));
	if (!scope)
		return (NULL);
	scope->input_fd = exec->input_fd;
	scope->output_fd = exec->output_fd;
	scope->pid = -1;
	scope->pipe = NULL;
	scope->scope_id = 1;
	return (scope);
}
