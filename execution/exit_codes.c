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
		exit_codes[i++] = HAS_NOT_RUN;
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
    exec->exit_codes[command_index] = exit_code>>8;
}

void	wait_until(t_executor *exec)
{
	int		i;
	int		exit_code;
	pid_t	pid;

	i = 0;
	while (get_exit_code(exec, i) != HAS_NOT_RUN)
		i++;
	while (i < exec->command_index + 1)
	{
        if (is_builtin(exec->cmds[i]))
        {
            i++;
            continue ;
        }
        else
        {
            pid = get_pid(exec, i);
            waitpid(pid, &exit_code, 0);
            set_exit_code(exec, i, exit_code);
            i++;
        }
	}
}

int	wait_check(t_cmd2 *cmd, t_cmd2 *cmds)
{
	if (!cmd || !cmds)
		terminate(cmds, EXIT_FAILURE, "couldn't check exit code");
    if (cmd->next == NULL || is_and_or(exec))
	{
        wait_until(exec);
		if (is_and_or(exec))
			evaluate_logic_operator(exec);
	}
	return (0);
}
