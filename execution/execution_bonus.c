
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
	exec->signal = EXECUTE;
	exec->status = 0;
	return (exec);
}

int	shell(t_executor *exec, t_scope *scope)
{
	if (!exec || !exec->cmds || !scope)
		terminate(NULL, NULL, EXIT_FAILURE);
	while (is_inside_scope(exec, scope))
	{
		if (has_nested_scope(exec, scope))
            execute_nested_scope(exec, scope);
        else
        {
            if (is_builtin(exec))
                execute_builtin(exec, scope);
            else
                execute_cmd(exec, scope);
            exec->command_index++;
        }
	}
	return (EXIT_SUCCESS);
}

int	execution(t_cmd **cmds)
{
	t_executor	*exec;
	t_scope	*scope;

	if (!cmds)
		terminate(NULL, NULL, EXIT_FAILURE);
	if (cmds[0] == NULL)
		terminate(NULL, NULL, EXIT_SUCCESS);
	exec = initialize_executor(cmds);
	if (!exec)
		terminate(NULL, NULL, EXIT_FAILURE);
	scope = initialize_scope();
	if (!scope)
		terminate(exec, NULL, EXIT_FAILURE);
	shell(exec, scope);
	terminate(exec, scope, EXIT_SUCCESS);
	return (0);
}
