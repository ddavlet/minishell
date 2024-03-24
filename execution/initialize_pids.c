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

pid_t	current_pid(t_executor *exec)
{
	if (!exec || !exec->pids)
		terminate(exec, EXIT_FAILURE, "finish him");
	return (exec->pids[exec->command_index]);
}
