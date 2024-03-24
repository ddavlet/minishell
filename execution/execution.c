#include "execution.h"

static t_executor	*initialize_executor(t_cmd **cmds, char **envp)
{
	t_executor	*exec;

	if (!cmds || !envp)
		return (NULL);
	exec = (t_executor *)ft_calloc(1, sizeof(t_executor));
	if (!exec)
		return (NULL);
	exec->cmds = cmds;
	exec->envp = envp;
	exec->command_index = 0;
	initialize_exit_codes(exec);
	initialize_pids(exec);
	initialize_pipes(exec);
	return (exec);
}

void    cmds_check(t_cmd **cmds)
{
	if (!cmds)
		terminate(NULL, EXIT_FAILURE, NULL);
	if (cmds[0] == NULL)
		terminate(NULL, EXIT_SUCCESS, NULL);
}

void    loop(t_executor *exec)
{
    if (is_builtin(exec))
        execute_builtin(exec);
    else
        execute_cmd(exec);
    if (is_final(exec) || is_logic(exec))
        check_exit(exec);
    if (get_current_cmd(exec)->operat == PIPE)
        close_next_pipe(exec);
    exec->command_index++;
}

int	execution(t_cmd **cmds, char **envp)
{
	t_executor	*exec;

    cmds_check(cmds);
	exec = initialize_executor(cmds, envp);
	if (!exec)
		terminate(NULL, EXIT_FAILURE, "failed to initialize executor");
	while (get_current_cmd(exec) != NULL)
		loop(exec);
	return (0);
}
