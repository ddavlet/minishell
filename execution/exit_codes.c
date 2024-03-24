#include "execution.h"

void	initialize_exit_codes(t_executor *exec)
{
	int	i;
	int	len;
	int	*exit_codes;

    len = get_execution_length(exec);
	exit_codes = (int *)ft_calloc(len + 1, sizeof(int));
	if (!exit_codes)
	{
		terminate(exec, EXIT_FAILURE, "couldn't allocate");
	}
	i = 0;
	while (i < len + 1)
		exit_codes[i++] = -1;
	exec->exit_codes = exit_codes;
}

int   get_exit_code(t_executor *exec, int command_index)
{
    if (!exec || !exec->pids)
        terminate(exec, EXIT_FAILURE, "couldn't get exit code");
    return (exec->exit_codes[command_index]);
}

void    set_exit_code(t_executor *exec, int command_index, int exit_code)
{
    if (!exec || !exec->pids)
        terminate(exec, EXIT_FAILURE, "couldn't set exit code");
    exec->exit_codes[command_index] = exit_code;
}

void	wait_until(t_executor *exec)
{
	int		i;
	int		exit_code;
	pid_t	pid;

	i = 0;
	while (get_exit_code(exec, i) != -1)
		i++;
	while (i < exec->command_index + 1)
	{
		pid = get_pid(exec);
		waitpid(pid, &exit_code, 0);
		set_exit_code(exec, i, exit_code);
	}
}

int	check_exit(t_executor *exec)
{

	if (!exec || !exec->cmds)
		terminate(NULL, EXIT_FAILURE, "parameter check failed");
    if (is_final(exec) || is_logic(exec))
	{
		if (is_logic(exec))
		{
			wait_until(exec);
			evaluate_logic_operator(exec);
		}
		else if (is_final(exec))
			wait_until(exec);
	}
	return (0);
}