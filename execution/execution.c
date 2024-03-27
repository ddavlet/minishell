#include "execution.h"

static t_executor	*initialize_executor(t_cmd **cmds, char **envp)
{
	t_executor	*exec;

	if (!cmds || !envp)
		return (NULL);
	exec = (t_executor *)ft_calloc(1, sizeof(t_executor));
	if (!exec)
		return (NULL);
    exec->stdin = dup(STDIN_FILENO);
    exec->stdout = dup(STDOUT_FILENO);
	exec->envp = envp;
	exec->cmds = cmds;
	exec->command_index = 0;
	initialize_exit_codes(exec);
	initialize_pids(exec);
	initialize_pipes(exec);
	return (exec);
}

static void    loop(t_executor *exec)
{
	while (get_current_cmd(exec))
    {
        set_input_output(exec);
        if (is_builtin(get_current_cmd(exec)))
            execute_builtin(exec);
        else
            execute_cmd(exec);
        if (is_final(exec) || is_logic(exec))
            wait_check(exec);
        reset_input_output(exec);
        exec->command_index++;
    }
}

int	execution(t_cmd **cmds, char **envp)
{
	t_executor	*exec;

    cmds_check(cmds);
	exec = initialize_executor(cmds, envp);
	if (!exec)
		terminate(exec, EXIT_FAILURE, "failed to initialize executor");
    loop(exec);
	return (0);
}
