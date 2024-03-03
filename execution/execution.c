
#include "execution.h"

static void	end_session(t_executor *exec, t_context *context)
{
	// if (is_last(exec))
    waitpid(context->pid, &(exec->status), 0);
	exit(exec->status);
}

t_executor	*initialize_executor(t_cmd **cmds)
{
	t_executor	*exec;

	if (!cmds)
		return (NULL);
	exec = (t_executor *)ft_calloc(1, sizeof(t_executor));
	if (!exec)
		return (NULL);
	exec->command_index = 0;
	exec->cmds = cmds;
	return (exec);
}

static int	execute_in_subshell(t_executor *exec, t_context *context)
{
	t_context	*subcontext;

	if (!exec || !exec->cmds || !context)
		terminate(NULL, NULL, EXIT_FAILURE);
	subcontext = create_subcontext(exec, context);
	if (subcontext == NULL)
		terminate(NULL, NULL, EXIT_FAILURE);
	subcontext->pid = fork();
	if (subcontext->pid == -1)
		terminate(NULL, subcontext, EXIT_FAILURE);
	if (subcontext->pid == 0)
	{
		if (subcontext->context_depth > 0)
			execute_in_subshell(exec, subcontext);
		exit(execute_context(exec, context));
	}
	else
		end_session(exec, context);
    return (0);
}

int	execution(t_cmd **cmds)
{
	t_executor	*exec;
	t_context	*context;

	if (!cmds)
		terminate(NULL, NULL, EXIT_FAILURE);
	if (cmds[0] == NULL)
		terminate(NULL, NULL, EXIT_SUCCESS);
	exec = initialize_executor(cmds);
	if (!exec)
		terminate(NULL, NULL, EXIT_FAILURE);
	context = initialize_context();
	if (!context)
		terminate(exec, NULL, EXIT_FAILURE);
	while (!has_finished(exec))
	{
		if (exec->signal == BUILTIN)
			execute_builtin(exec, context);
		else
			execute_in_subshell(exec, context);
	}
	terminate(exec, context, EXIT_SUCCESS);
    return (0);
}
