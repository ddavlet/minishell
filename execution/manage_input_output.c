#include "execution.h"

static int	output_redir(t_executor *exec, t_scope *scope)
{
    t_cmd   *cmd;
    t_cmd   *next;

    cmd = current_cmd_in_execution(exec);
    next = next_cmd_in_execution(exec);
    if (cmd->operat == PIPE && connected_through_operation(cmd, next))
		dup2(scope->pipe->write->fd, STDOUT_FILENO);
    close(scope->pipe->write->fd);
	if (cmd->redirs != NULL)
	{
		if (scope->output_fd != STDOUT_FILENO)
			close(scope->output_fd);
		scope->output_fd = last_output_redir(exec);
		if (scope->output_fd == -1)
			return (-1);
        dup2(scope->output_fd, STDOUT_FILENO);
		close(scope->output_fd);
	}
	// ft_putstr_fd("DEBUG::out_fd: ", 2);
    // ft_putendl_fd(ft_itoa(scope->output_fd), 2);
	return (0);
}

static int	input_redir(t_executor *exec, t_scope *scope)
{
    t_cmd   *cmd;
    t_cmd   *last;

    cmd = current_cmd_in_execution(exec);
    last = last_cmd_in_execution(exec);
    if (last->operat == PIPE && connected_through_operation(cmd, last))
		dup2(scope->pipe->read->fd, STDIN_FILENO);
    //close(scope->pipe->read->fd);
    if (cmd->redirs != NULL)
	{
		if (scope->input_fd != STDIN_FILENO)
			close(scope->input_fd);
		scope->input_fd = last_input_redir(exec, scope);
		if (scope->input_fd == -1)
			return (-1);
        dup2(scope->input_fd, STDIN_FILENO);
		close(scope->input_fd);
	}
	// ft_putstr_fd("DEBUG::in_fd: ", 2);
    // ft_putendl_fd(ft_itoa(scope->input_fd), 2);
	return (0);
}

int manage_input_output(t_executor *exec, t_scope *scope)
{
	if (scope->output_fd != STDOUT_FILENO)
        dup2(scope->output_fd, STDOUT_FILENO);
	if (scope->input_fd != STDIN_FILENO)
        dup2(scope->input_fd, STDIN_FILENO);
	if (output_redir(exec, scope) == -1)
        return (-1);
	if (input_redir(exec, scope) == -1)
        return (-1);
}