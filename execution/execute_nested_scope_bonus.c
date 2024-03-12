#include "execution.h"

void    debug_execute_nested_scope(t_scope *scope, t_executor *exec)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd("DEBUG:execute_nested_scope: child process begins", 2);
    ft_putstr_fd("DEBUG::scope:input: ", STDERR_FILENO);
    ft_putnbr_fd(scope->input_fd->fd, STDERR_FILENO);
    ft_putendl_fd("", STDERR_FILENO);
    ft_putstr_fd("DEBUG::scope:output: ", STDERR_FILENO);
    ft_putnbr_fd(scope->output_fd->fd, STDERR_FILENO);
    ft_putendl_fd("", STDERR_FILENO);
    ft_putstr_fd("DEBUG::scope_id: ", STDERR_FILENO);
    ft_putnbr_fd(scope->scope_id, STDERR_FILENO);
    ft_putendl_fd("", STDERR_FILENO);
    ft_putstr_fd("DEBUG::first command_index: ", STDERR_FILENO);
    ft_putnbr_fd(exec->command_index, STDERR_FILENO);
    ft_putendl_fd("", STDERR_FILENO);

    
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
}

void    debug_execute_nested_scope_1(t_executor *exec, t_scope *scope)
{
    ft_putendl_fd("DEBUG::execute_nested_scope: parent begins", STDERR_FILENO);
    ft_putstr_fd("DEBUG::nested_id: ", STDERR_FILENO);
    ft_putnbr_fd(get_nested_id(exec, scope->scope_id), STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}

void    debug_execute_nested_scope_2(t_executor *exec, t_scope *scope)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd("DEBUG::execute_nested_scope: fork child", STDERR_FILENO);
    ft_putstr_fd("DEBUG::command_id: ", STDERR_FILENO);
    ft_putnbr_fd(exec->command_index, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
}

void    debug_execute_nested_scope_3(t_executor *exec, t_scope *scope)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd("DEBUG::execute_nested_scope: child process ends", STDERR_FILENO);
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
}

void    debug_execute_nested_scope_4(t_executor *exec, t_scope *scope)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd("DEBUG::execute_nested_scope: parent continues", STDERR_FILENO);
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
}

void    debug_execute_nested_scope_5(t_executor *exec, t_scope *scope)
{
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
    ft_putendl_fd("DEBUG::execute_nested_scope: parent process ends", STDERR_FILENO);
    ft_putendl_fd("::::::::::::::::::::::::::::::::", 2);
}

int	execute_nested_scope(t_executor *exec, t_scope *scope)
{
    t_scope	*nested_scope;

    nested_scope = create_nested_scope(exec, scope);
    if (!nested_scope)
        terminate(NULL, NULL, EXIT_FAILURE, "execute_nested_scope: couldn't create nested scope");
    debug_execute_nested_scope_1(exec, scope);
    close_fd(scope->pipe->write, exec);
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "execute_nested_scope: parameter check failed");
    debug_execute_nested_scope_2(exec, scope);
	scope->pid = fork();
	if (scope->pid == -1)
		terminate(NULL, NULL, EXIT_FAILURE, NULL);
	else if (scope->pid == 0)
	{
        debug_execute_nested_scope(nested_scope, exec);
        shell(exec, nested_scope);
        debug_execute_nested_scope_3(exec, nested_scope);
		exit(0);
	}
	else
	{
        debug_execute_nested_scope_4(exec, scope);
        check_exit_value(exec, scope);
		exec->command_index += scope_length(exec, nested_scope->scope_id);
	}
    debug_execute_nested_scope_5(exec, scope);    
	return (0);
}
