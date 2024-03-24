#include "execution.h"

void	initialize_pids(t_executor *exec)
{
	int		i;
	pid_t	*pids;

	pids = (pid_t *)ft_calloc(exec->size + 1, sizeof(pid_t));
	if (!pids)
	{
		terminate(exec, EXIT_FAILURE, "error");
	}
	i = 0;
	while (i < exec->size)
		pids[i++] = -1;
	exec->pids = pids;
}

pid_t   get_pid(t_executor *exec)
{
    if (!exec || !exec->pids)
        terminate(exec, EXIT_FAILURE, "couldn't get pid");
    return (exec->pids[exec->command_index]);
}

void    set_pid(t_executor *exec, pid_t pid)
{
    if (!exec || !exec->pids)
        terminate(exec, EXIT_FAILURE, "couldn't set pid");
    exec->pids[exec->command_index] = pid;
}