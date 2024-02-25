
#include "execution.h"

t_executor	*initialize_executor(t_cmd **cmds, char *envp[])
{
    t_executor    *executor;
    e_logic_op    *priority_stack;

	if (!cmds || !envp)
		return (NULL);
	executor = (t_executor *)malloc(sizeof(t_executor));
	if (!executor)
		return (NULL);
    priority_stack = (e_logic_op *)malloc(sizeof(e_logic_op) * arr_length((void **)cmds));
	executor->in_fd = 0;
	executor->out_fd = 1;
	executor->pipe_fd[0] = 0;
	executor->pipe_fd[1] = 0;
	executor->pid = 0;
	executor->fd_count = 0;
	executor->status = 0;
	executor->cmds = cmds;
    executor->priority_stack
	return (executor);
}

int	execution(t_cmd **cmds, char *envp[])
{
	t_executor	*executor;

	executor = initialize_executor(cmds, envp);
	if (!executor)
		return (-1);
	if (!cmds || cmds[0] == NULL)
	{
		terminate_execution(executor);
		return (-1);
	}
	execute_loop(executor);
	terminate_execution(executor);
	return (0);
}
