#include "execution.h"

static int	same_depth(t_context *subcontext, t_cmd *cmd)
{
	if (cmd->context_depth == subcontext->context_depth)
		return (1);
	return (0);
}

static int	set_before_after(t_executor *exec, t_context *subcontext)
{
	t_cmd	*first_cmd;
	int		next;

	if (!exec || !exec->cmds || !subcontext)
		return (-1);
	if (exec->command_index == 0)
		subcontext->oper_before = RUN;
	else
		subcontext->oper_before = exec->cmds[exec->command_index - 1]->operat;
	first_cmd = exec->cmds[exec->command_index];
	next = exec->command_index + 1;
	while (exec->cmds[next] != NULL && subcontext->context_depth > 0
		&& same_depth(subcontext, exec->cmds[next]))
		next++;
	subcontext->oper_after = exec->cmds[next - 1]->operat;
	return (0);
}

static int	set_input_output(t_executor *exec, t_context *subcontext,
		t_context *context)
{
	// Add seqfault protections
	if (subcontext->oper_before == PIPE)
    {
        if (context->pipe == NULL)
            return (-1);
		subcontext->input_fd = context->pipe->read->fd;
    }
	else
		subcontext->input_fd = STDIN_FILENO;
	if (subcontext->oper_after == PIPE)
    {
        if (context->pipe == NULL)
            return (-1);
		subcontext->output_fd = context->pipe->write->fd;
    }
	else
		subcontext->output_fd = STDOUT_FILENO;
}

t_context	*create_subcontext(t_executor *exec, t_context *context)
{
	t_context	*subcontext;

	subcontext = (t_context *)ft_calloc(1, sizeof(t_context));
	if (!subcontext)
		return (NULL);
	if (set_before_after(exec, subcontext) == -1
		|| set_input_output(exec, subcontext, context) == -1)
	{
		free(subcontext);
		return (NULL);
	}
	context->pipe = create_pipe();
	if (context->pipe == NULL)
	{
		free(subcontext);
		return (NULL);
	}
	if (context->context_depth == 0)
		subcontext->context_depth = exec->cmds[exec->command_index]->context_depth;
	else
		subcontext->context_depth = context->context_depth - 1;
	subcontext->pid = -1;
	return (subcontext);
}

t_context	*initialize_context(t_executor *exec)
{
	t_context	*context;

	context = (t_context *)ft_calloc(1, sizeof(t_context));
	if (!context)
		return (NULL);
	context->pipe = create_pipe();
	if (context->pipe == NULL)
	{
		free(context);
		return (NULL);
	}
	context->input_fd = STDIN_FILENO;
	context->output_fd = STDOUT_FILENO;
	context->oper_after = RUN;
	context->oper_before = RUN;
	context->pid = -1;
	// context->pipe = NULL;
	context->context_depth = -1;
}
