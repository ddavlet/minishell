#include "execution.h"

static int	set_before_after_operation(t_executor *exec, t_context *subcontext)
{
	t_cmd	*first_cmd;
	int		last;

	if (!exec || !exec->cmds || !subcontext)
		return (-1);
	if (exec->command_index == 0)
		subcontext->oper_before = RUN;
	else
		subcontext->oper_before = exec->cmds[exec->command_index - 1]->operat;
	first_cmd = exec->cmds[exec->command_index];
	last = exec->command_index;
	while (exec->cmds[last + 1] != NULL
		&& exec->cmds[last]->context_depth == first_cmd->context_depth)
		last++;
	subcontext->oper_after = exec->cmds[last]->operat;
	return (0);
}

static int	set_input_output_stream(t_executor *exec, t_context *subcontext,
		t_context *context)
{
	// Add seqfault protections
	if (subcontext->oper_before == PIPE)
		subcontext->input_fd = context->pipe->read->fd;
	else
		subcontext->input_fd = STDIN_FILENO;
	if (subcontext->oper_after == PIPE)
		subcontext->output_fd = context->pipe->write->fd;
	else
		subcontext->output_fd = STDOUT_FILENO;
}

t_context	*create_subcontext(t_executor *exec, t_context *context)
{
	t_context	*subcontext;

	subcontext = (t_context *)ft_calloc(1, sizeof(t_context));
	if (!subcontext)
		return (NULL);
	if (set_before_after_operation(exec, subcontext) == -1
		|| set_input_output_stream(exec, subcontext, context) == -1)
	{
		free(subcontext);
		return (NULL);
	}
	subcontext->context_depth = context->context_depth - 1;
	subcontext->pipe = NULL;
	subcontext->pid = -1;
	subcontext->status = 1;
	return (subcontext);
}

t_context	*initialize_context(t_executor *exec)
{
	t_context	*context;

	context = (t_context *)ft_calloc(1, sizeof(t_context));
	if (!context)
		return (NULL);
	context->pipe = NULL;
	context->input_fd = STDIN_FILENO;
	context->output_fd = STDOUT_FILENO;
	context->oper_after = RUN;
	context->oper_before = RUN;
	context->pid = -1;
	context->context_depth = exec->cmds[exec->command_index]->context_count;
}
