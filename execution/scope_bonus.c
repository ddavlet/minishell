#include "execution.h"

int	set_before(t_executor *exec, t_scope *subscope)
{
	t_cmd	*first_cmd_in_subscope;
	t_cmd	*prev;

	if (param_check(exec, subscope))
		return (-1);
	if (exec->command_index == 0)
		subscope->oper_before = RUN;
	else
	{
		first_cmd_in_subscope = exec->cmds[exec->command_index];
		prev = exec->cmds[exec->command_index - 1];
		if (get_scope(first_cmd_in_subscope) == get_scope(prev)
			|| get_outside_scope(first_cmd_in_subscope) == get_scope(prev)
			|| get_outside_scope(first_cmd_in_subscope) == get_outside_scope(prev))
			subscope->oper_before = prev->operat;
		else
			subscope->oper_before = RUN;
	}
    return (0);
}

int	set_after(t_executor *exec, t_scope *subscope)
{
	t_cmd	*last_cmd_in_subscope;
	t_cmd	*next;

	if (param_check(exec, subscope))
		return (-1);
	last_cmd_in_subscope = get_last_cmd_in_scope(exec, subscope);
	next = next_cmd_in_execution(exec);
	if (next == NULL)
		subscope->oper_before = RUN;
	else
	{
		if (get_scope(last_cmd_in_subscope) == get_scope(next)
			|| get_outside_scope(last_cmd_in_subscope) == get_scope(next)
			|| get_outside_scope(last_cmd_in_subscope) == get_outside_scope(prev))
			subscope->oper_before = prev->operat;
		else
			subscope->oper_before = RUN;
	}
    return (0);
}

static int	set_input_output(t_scope *subscope, t_scope *scope)
{
	if (!subscope || !scope)
        return (-1);
	if (subscope->oper_before == PIPE)
	{
		if (scope->pipe == NULL)
			return (-1);
		subscope->input_fd = scope->pipe->read->fd;
	}
	else
		subscope->input_fd = STDIN_FILENO;
	if (subscope->oper_after == PIPE)
	{
		if (scope->pipe == NULL)
			return (-1);
		subscope->output_fd = scope->pipe->write->fd;
	}
	else
		subscope->output_fd = STDOUT_FILENO;
	return (0);
}

t_scope	*create_nested_scope(t_executor *exec, t_scope *scope)
{
	t_scope	*nested_scope;

	nested_scope = (t_scope *)ft_calloc(1, sizeof(t_scope));
	if (!nested_scope)
		return (NULL);
	if (set_before(exec, nested_scope) == -1 || set_after(exec, nested_scope) ==
		-1 || set_input_output(nested_scope, scope) == -1)
        terminate(NULL, nested_scope, EXIT_FAILURE);
	scope->pipe = create_pipe();
	if (scope->pipe == NULL)
        terminate(NULL, nested_scope, EXIT_FAILURE);
	nested_scope->scope_id = find_nested_id(exec, scope);
    if (!nested_scope->scope_id)
        terminate(NULL, nested_scope, EXIT_FAILURE);
	nested_scope->pid = -1;
	return (nested_scope);
}

t_scope	*initialize_scope(void)
{
	t_scope	*scope;

	scope = (t_scope *)ft_calloc(1, sizeof(t_scope));
	if (!scope)
		return (NULL);
	scope->pipe = create_pipe();
	if (scope->pipe == NULL)
	{
		free(scope);
		return (NULL);
	}
	scope->input_fd = STDIN_FILENO;
	scope->output_fd = STDOUT_FILENO;
	scope->oper_after = RUN;
	scope->oper_before = RUN;
    scope->scope_id = 1;
	scope->pid = -1;
	// scope->pipe = NULL;
	return (scope);
}
