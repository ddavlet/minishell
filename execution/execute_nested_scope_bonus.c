#include "execution.h"

void    debug_execute_nested_scope(t_scope *scope, t_executor *exec)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd("DEBUG:execute_nested_scope child process begins", 2);
    ft_putstr_fd("scope_id: ", STDERR_FILENO);
    ft_putnbr_fd(scope->scope_id, STDERR_FILENO);
    ft_putstr_fd("::pid: ", STDERR_FILENO);
    ft_putnbr_fd(scope->pid, STDERR_FILENO);
    ft_putstr_fd("::command_index: ", STDERR_FILENO);
    ft_putnbr_fd(exec->command_index, STDERR_FILENO);

    ft_putstr_fd("::scope->input_fd->fd: ", STDERR_FILENO);
    ft_putnbr_fd(scope->input_fd->fd, STDERR_FILENO);
    ft_putstr_fd("::scope->output_fd->fd: ", STDERR_FILENO);
    ft_putnbr_fd(scope->output_fd->fd, STDERR_FILENO);
    ft_putendl_fd("", STDERR_FILENO);
    
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
}

int	execute_nested_scope(t_executor *exec, t_scope *scope)
{
    ft_putstr_fd("DEBUG::execute_nested_scope: parent begins", STDERR_FILENO);
    ft_putstr_fd("::nested_id: ", STDERR_FILENO);
    ft_putnbr_fd(get_nested_id(exec, scope->scope_id), STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);

	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "execute_nested_scope: parameter check failed");
	scope->pipe = NULL;

    ft_putstr_fd("DEBUG::execute_nested_scope: fork child", STDERR_FILENO);
    ft_putstr_fd("::command_id: ", STDERR_FILENO);
    ft_putnbr_fd(exec->command_index, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);

	scope->pid = fork();
	if (scope->pid == -1)
		terminate(NULL, NULL, EXIT_FAILURE, NULL);
	else if (scope->pid == 0)
	{
		scope = create_nested_scope(exec, scope);
        debug_execute_nested_scope(scope, exec);
        shell(exec, scope);

        ft_putendl_fd("DEBUG::execute_nested_scope: child process ends", STDERR_FILENO);

		exit(0);
	}
	else
	{
        ft_putendl_fd("DEBUG::execute_nested_scope: parent continues", STDERR_FILENO);
		check_exit_value(exec, scope);
		exec->command_index += scope_length(exec, get_nested_id(exec,
					scope->scope_id));
	}
    ft_putendl_fd("DEBUG::execute_nested_scope: parent process ends", STDERR_FILENO);
	return (0);
}

// ft_printf("DEBUG:loop.c: pipe_fd[0]: %d\n", exec->pipe_fd[0]);
// ft_printf("DEBUG:loop.c: pipe_fd[1]: %d\n", exec->pipe_fd[1]);