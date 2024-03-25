#include "execution.h"

void	initialize_pids(t_executor *exec)
{
	int		i;
	pid_t	*pids;
    int     size;

    size = get_execution_length(exec) + 1;
	pids = (pid_t *)ft_calloc(size, sizeof(pid_t));
	if (!pids)
	{
		terminate(exec, EXIT_FAILURE, "error");
	}
	i = 0;
	while (i < size)
		pids[i++] = -1;
	exec->pids = pids;
}

pid_t   get_pid(t_executor *exec, int command_index)
{
    if (!exec || !exec->pids)
        terminate(exec, EXIT_FAILURE, "couldn't get pid");
    return (exec->pids[command_index]);
}

void    set_pid(t_executor *exec, int command_index, pid_t pid)
{
    if (!exec || !exec->pids)
        terminate(exec, EXIT_FAILURE, "couldn't set pid");
    exec->pids[command_index] = pid;
}