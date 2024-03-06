#include "execution.h"

static int	output_redir(t_executor *exec, t_scope *scope)
{
    t_cmd   *cmd;

    cmd = exec->cmds[exec->command_index];
	if (cmd->redirs != NULL)
	{
		if (scope->output_fd != STDOUT_FILENO)
			close(scope->output_fd);
		scope->output_fd = last_output_redir(exec);
		if (scope->output_fd == -1)
			return (-1);
	}
	ft_printf("out_fd: %d\n", scope->output_fd);
	dup2(scope->output_fd, STDOUT_FILENO);
	if (scope->output_fd != STDOUT_FILENO)
		close(scope->output_fd);
	return (0);
}

static int	input_redir(t_executor *exec, t_scope *scope)
{
    t_cmd   *cmd;

    cmd = exec->cmds[exec->command_index];
	if (cmd->redirs != NULL)
	{
		if (scope->input_fd != STDIN_FILENO)
			close(scope->input_fd);
		scope->input_fd = last_input_redir(exec, scope);
		if (scope->input_fd == -1)
			return (-1);
	}
	ft_printf("in_fd: %d\n", scope->input_fd);
	dup2(scope->input_fd, STDIN_FILENO);
	if (scope->input_fd != STDIN_FILENO)
		close(scope->input_fd);
	return (0);
}

int manage_input_output(t_executor *exec, t_scope *scope)
{
    t_cmd   *cmd;
    
	cmd = exec->cmds[exec->command_index];
    // (void)exec;
    // (void)scope;
    // (void)cmd;
    if (cmd->operat == PIPE)
		dup2(scope->pipe->write->fd, STDOUT_FILENO);
	output_redir(exec, scope);
	input_redir(exec, scope);
    if (cmd->operat == PIPE)
        close(scope->pipe->write->fd);
}