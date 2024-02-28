
#include "execution.h"

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

int	execution(t_cmd **cmds)
{
	t_executor	*exec;
	t_context	*context;

	if (!cmds)
		return (-1);
	if (cmds[0] == NULL)
		return (0);
	exec = initialize_executor(cmds);
	if (!exec)
		return (-1);
	context = initialize_context();
	if (!context)
		exit_handler();
	execute_in_subshell(exec, context);
	return (0);
}

int	execute_in_subshell(t_executor *exec, t_context *context)
{
	t_context	*subcontext;
	t_cmd	*current_cmd;

	current_cmd = exec->cmds[exec->command_index];
	subcontext = create_subcontext(exec, context);
	subcontext->pid = fork();
	if (subcontext->pid == -1)
		exit_handler();
	if (subcontext->pid == 0)
	{
		if (subcontext->context_depth > 0)
			exit(execute_in_subshell(exec, context));
		exit(execute_context(exec, context));
	}
	else
		exit_value(exec, subcontext);
}

void	exit_value(t_executor *exec, t_context *context)
{
	waitpid(context->pid, &(context->status), 0);
}

void	exit_handler(void)
{
	return ;
}
