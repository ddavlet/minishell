
#include "execution.h"

t_executor	*initialize_executor(t_cmd **cmds, char *envp[])
{
    t_executor    *exec;
    e_logic_op    *priority_stack;

	if (!cmds || !envp)
		return (NULL);
	exec = (t_executor *)calloc(sizeof(t_executor));
	if (!exec)
		return (NULL);
    priority_stack = initialize_priority_stack(cmds);
    if (!priority_stack)
    {
        free(exec);
        return (NULL);
    }
	exec->cmds = cmds;
	exec->fd_count = 0;
	exec->in_fd = 0;
	exec->out_fd = 1;
	exec->pid = 0;
    exec->priority_stack = priority_stack;
	exec->status = 0;
	return (exec);
}

int	execution(t_cmd **cmds, char *envp[])
{
	t_executor	*exec;

	exec = initialize_executor(cmds, envp);
	if (!exec)
		return (-1);
	if (!cmds || cmds[0] == NULL)
	{
		terminate_execution(exec);
		return (-1);
	}
	execute_loop(exec);
	terminate_execution(exec);
	return (0);
}
