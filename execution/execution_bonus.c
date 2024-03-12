#include "execution.h"

void    debug_shell_1(t_executor *exec, t_scope *scope)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd("DEBUG::execution begins", STDERR_FILENO);
    ft_putstr_fd("DEBUG::scope_id::", STDERR_FILENO);
    ft_putnbr_fd(scope->scope_id, STDERR_FILENO);
    ft_putchar_fd('\n', STDERR_FILENO);
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
}

void    debug_shell_2(t_executor *exec, t_scope *scope)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd("DEBUG::execution ends", STDERR_FILENO);
    ft_putstr_fd("DEBUG::scope_id::", STDERR_FILENO);
    ft_putnbr_fd(scope->scope_id, STDERR_FILENO);
    ft_putchar_fd('\n', STDERR_FILENO);
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
}

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
	exec->status = 0;
    exec->input_fd = initialize_fd_state(STDIN_FILENO);
    exec->output_fd = initialize_fd_state(STDOUT_FILENO);
    if (!exec->input_fd || !exec->output_fd)
        terminate(NULL, NULL, EXIT_FAILURE, "failed to initialize executor");
	return (exec);
}

int	shell(t_executor *exec, t_scope *scope)
{
    debug_shell_1(exec, scope);
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	while (is_inside_scope(current_cmd_in_execution(exec), scope->scope_id))
	{
		if (has_nested_scope(exec, scope))
            execute_nested_scope(exec, scope);
        else
        {
            if (is_builtin(exec))
                execute_builtin(exec, scope);
            else
                execute_cmd(exec, scope);
        }
	}
    debug_shell_2(exec, scope);
	return (EXIT_SUCCESS);
}

int	execution(t_cmd **cmds)
{
	t_executor	*exec;
	t_scope	*scope;

	if (!cmds)
		terminate(NULL, NULL, EXIT_FAILURE, NULL);
	if (cmds[0] == NULL)
		terminate(NULL, NULL, EXIT_SUCCESS, NULL);
	exec = initialize_executor(cmds);
	if (!exec)
		terminate(NULL, NULL, EXIT_FAILURE, NULL);
	scope = initialize_scope(exec);
	if (!scope)
		terminate(exec, NULL, EXIT_FAILURE, NULL);
	shell(exec, scope);
	terminate(exec, scope, EXIT_SUCCESS, NULL);
	return (0);
}
