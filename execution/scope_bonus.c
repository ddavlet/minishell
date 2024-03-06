#include "execution.h"

static int	set_input_output(t_executor *exec, t_scope *subscope,
		t_scope *scope)
{
	if (!subscope || !scope)
		return (-1);
	if (operation_before(exec, subscope) == PIPE)
	{
		if (scope->pipe == NULL)
			return (-1);
		subscope->input_fd = scope->pipe->read->fd;
	}
	else
		subscope->input_fd = STDIN_FILENO;
	if (operation_after(exec, subscope) == PIPE)
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
	nested_scope->scope_id = find_nested_id(exec, scope);
	if (!(nested_scope->scope_id))
		terminate(NULL, nested_scope, EXIT_FAILURE);
	if (set_input_output(exec, nested_scope, scope) == -1)
		terminate(NULL, nested_scope, EXIT_FAILURE);
	scope->pipe = create_pipe();
	if (scope->pipe == NULL)
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
	scope->scope_id = 1;
	scope->pid = -1;
	// scope->pipe = NULL;
	return (scope);
}
