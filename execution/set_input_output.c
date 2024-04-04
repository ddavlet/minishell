#include "execution.h"

void	handle_pipe_output(t_executor *exec)
{
	t_pipe	*pipe;

	pipe = next_pipe(exec->pipes);
	if (dup2(pipe->write->fd, STDOUT_FILENO) == -1)
		terminate(exec, EXIT_FAILURE,
			"minishell: unable to set pipe to output");
	close_fd(pipe->write);
}

void	handle_redir_output(t_executor *exec)
{
	t_fd_state	*output_fd;

	output_fd = last_output_redir(exec);
	if (output_fd)
	{
		if (dup2(output_fd->fd, STDOUT_FILENO) == -1)
			terminate(exec, EXIT_FAILURE, "minishell: unable to set output");
		if (output_fd->fd != STDOUT_FILENO)
			close_fd(output_fd);
	}
}

void	handle_pipe_input(t_executor *exec)
{
	t_pipe	*pipe;

	pipe = last_pipe(exec->pipes);
	if (!pipe)
		terminate(exec, EXIT_FAILURE, "Failed to set pipe to input");
	if (dup2(pipe->read->fd, STDIN_FILENO) == -1)
		terminate(exec, EXIT_FAILURE, "minishell: unable to set pipe to input");
}

int	handle_redir_input(t_cmd2 *cmd)
{
	t_fd_state	*input_fd;

	input_fd = last_input_redir(cmd);
	if (input_fd)
	{
		if (dup2(input_fd->fd, STDIN_FILENO) == -1)
			ft_putstr_fd("minishell: unable to set pipe to output", STDERR_FILENO);
		if (input_fd->fd != STDIN_FILENO)
			close_fd(input_fd);
	}
}

void	set_input_output(t_cmd2 *cmd, t_cmd2 *cmds)
{
	t_cmd *prev;
	t_cmd *next;

	prev = get_previous_cmd(cmds, cmd);
	next = get_next_cmd(cmds, cmd);
	if (cmd->redirections)
		if (handle_redir_input(cmd) == -1 || handle_redir_output(cmd) == -1)
			terminate(cmds, EXIT_FAILURE, "failed redirections");
	if (prev && prev->operat == PIPE)
		if (handle_pipe_input(cmds) == -1)
			terminate(cmds, EXIT_FAILURE, "failed pipe input");
	if (next && cmd->operat == PIPE)
		if (handle_pipe_output(cmds) == -1)
			terminate(cmds, EXIT_FAILURE, "failed pipe output");
}