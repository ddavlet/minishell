#include "execution.h"

static void  debug_child_process(t_executor *exec, t_scope *scope, char *path)
{
	ft_putendl_fd("::::::::::::::::::::::::", 2);

	ft_putstr_fd("DEBUG::execve::", 2);
	ft_putendl_fd(argv(exec)[0], 2);
	ft_putstr_fd("DEBUG::path::", 2);
	ft_putendl_fd(path, 2);
	ft_putstr_fd("DEBUG::out_fd::", 2);
	ft_putendl_fd(ft_itoa(exec->output_fd->fd), 2);
	ft_putstr_fd("DEBUG::in_fd::", 2);
	ft_putendl_fd(ft_itoa(exec->input_fd->fd), 2);
	ft_putstr_fd("DEBUG::pipe->read::", 2);
	ft_putendl_fd(ft_itoa(scope->pipe->read->fd), 2);
	ft_putstr_fd("DEBUG::pipe->write::", 2);
	ft_putendl_fd(ft_itoa(scope->pipe->write->fd), 2);
	ft_putendl_fd("::fd_state before execve::", 2);
	ft_putstr_fd("DEBUG::out_fd->is_open::", 2);
	ft_putendl_fd(ft_itoa(exec->output_fd->is_open), 2);
	ft_putstr_fd("DEBUG::in_fd->is_open::", 2);
	ft_putendl_fd(ft_itoa(exec->input_fd->is_open), 2);
	ft_putstr_fd("DEBUG::pipe->read->is_open::", 2);
	ft_putendl_fd(ft_itoa(scope->pipe->read->is_open), 2);
	ft_putstr_fd("DEBUG::pipe->write->is_open::", 2);
	ft_putendl_fd(ft_itoa(scope->pipe->write->is_open), 2);

}

static int	set_output(t_executor *exec, t_scope *scope)
{
	if (current_cmd_in_execution(exec)->operat == PIPE
		&& next_cmd_connected_through_operation(exec))
    {
        exec->output_fd = scope->pipe->write;
        if (dup2(exec->output_fd->fd, STDOUT_FILENO) == -1)
            terminate(NULL, NULL, EXIT_FAILURE, "minishell: unable to set pipe to output");
        close_fd(exec->output_fd, exec);
    }
	if (current_cmd_in_execution(exec)->redirs != NULL)
	{
		// if (exec->output_fd->fd != STDOUT_FILENO)
		// 	close_fd(exec->output_fd);
		exec->output_fd = last_output_redir(exec);
		if (exec->output_fd == NULL)
			return (-1);
        if (dup2(exec->output_fd->fd, STDOUT_FILENO) == -1)
            terminate(NULL, NULL, EXIT_FAILURE, "minishell: unable to set output");
        if (exec->output_fd->fd != STDOUT_FILENO)
            close_fd(exec->output_fd, exec);
	}
	return (0);
}

static int	set_input(t_executor *exec, t_scope *scope)
{
	if (current_cmd_in_execution(exec)->redirs != NULL)
	{
		if (exec->input_fd->fd != STDIN_FILENO)
			close_fd(exec->input_fd, exec);
		exec->input_fd = last_input_redir(exec, scope);
		if (exec->input_fd == NULL)
			return (-1);
	}
	dup2(exec->input_fd->fd, STDIN_FILENO);
	if (exec->input_fd->fd != STDIN_FILENO)
		close_fd(exec->input_fd,exec);
	return (0);
}

static int	child_process(t_executor *exec, t_scope *scope)
{
	char	*path;

	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	path = get_path(argv(exec)[0], envp(exec));
	if (path == NULL)
		terminate(NULL, NULL, EXIT_FAILURE, "minishell: couldn't find path");
	if (set_input(exec, scope) == -1 || set_output(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE,
			"minishell: unable to set input/output");
    close_pipe(scope->pipe, exec);
	// *** DEBUG
    debug_child_process(exec, scope, path);
	// ***
	if (execve(path, argv(exec), envp(exec)) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "minishell: execution failure");
	return (0);
}

static void debug_prepare_next(t_executor *exec, t_scope *scope)
{
    ft_putstr_fd("execute_cmd::cmd[", 2);
    ft_putnbr_fd(exec->command_index, 2);
    ft_putstr_fd("]::pid::", 2);
    ft_putnbr_fd(scope->pid, 2);
    ft_putstr_fd("::scope_id::", 2);
    ft_putnbr_fd(scope->scope_id, 2);
    ft_putstr_fd("::EXIT_SUCCESS::", 2);
    ft_putchar_fd('\n', 2);
}

static void	prepare_next(t_executor *exec, t_scope *scope)
{
	exec->input_fd = scope->input_fd;
	exec->output_fd = scope->output_fd;
	// if (exec->input_fd->fd != STDIN_FILENO && exec->input_fd != scope->input_fd)
	// 	close_fd(exec->input_fd, exec);
	if (current_cmd_in_execution(exec)->operat == PIPE
		&& next_cmd_connected_through_operation(exec))
		exec->input_fd = scope->pipe->read;
	else
		close_fd(scope->pipe->read, exec);
    // *** DEBUG INFO ***
    debug_prepare_next(exec, scope);
    // *** DEBUG INFO ***
}

int	execute_cmd(t_executor *exec, t_scope *scope)
{
	if (param_check(exec, scope) == -1)
		terminate(NULL, NULL, EXIT_FAILURE, "parameter check failed");
	scope->pipe = create_pipe();
	if (scope->pipe == NULL)
		terminate(NULL, NULL, EXIT_FAILURE, "Couldn't create pipe");
	scope->pid = fork();
	if (scope->pid == -1)
		terminate(NULL, scope, EXIT_FAILURE, NULL);
	if (scope->pid == 0)
		child_process(exec, scope);
	else
	{
		check_exit_value(exec, scope);
		prepare_next(exec, scope);
	}
    return (0);
}
