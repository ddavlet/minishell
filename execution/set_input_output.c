#include "execution.h"

void	handle_pipe_output(t_cmd2 *cmd)
{
	t_pipe	*pipe;

	cmd_check(cmd);
	if (!pipe)
		terminate(cmd, EXIT_FAILURE,
			"minishell: failed to set pipe to output: missing pipe");
	pipe = cmd->execution->pipe;
	if (dup2(pipe->write->fd, STDOUT_FILENO) == -1)
		terminate(cmd, EXIT_FAILURE,
			"minishell: unable to set pipe to output");
	close_fd(pipe->write);
}

void	handle_redir_output(t_cmd2 *cmd)
{
	t_fd_state	*output_fd;

	cmd_check(cmd);
	output_fd = last_output_redir(cmd);
	if (output_fd)
	{
		if (dup2(output_fd->fd, STDOUT_FILENO) == -1)
			terminate(cmd, EXIT_FAILURE,
				"minishell: failed dup2 for output redirection");
		if (output_fd->fd != STDOUT_FILENO)
			close_fd(output_fd);
	}
}

void	handle_pipe_input(t_cmd2 *cmd)
{
	t_pipe	*pipe;
	t_cmd2	*prev;

	cmd_check(cmd);
	prev = get_previous_cmd(cmd);
	pipe = prev->execution->pipe;
	if (!pipe)
		terminate(cmd, EXIT_FAILURE,
			"minishell: failed to set pipe to input: missing pipe");
	if (dup2(pipe->read->fd, STDIN_FILENO) == -1)
		terminate(cmd, EXIT_FAILURE,
			"minishell: failed dup2 for pipe input redirection");
}

void	handle_redir_input(t_cmd2 *cmd)
{
	t_fd_state	*input_fd;

	cmd_check(cmd);
	input_fd = last_input_redir(cmd);
	if (input_fd)
	{
		if (dup2(input_fd->fd, STDIN_FILENO) == -1)
			terminate(cmd, EXIT_FAILURE,
				"minishell: failed dup2 for input redirection");
		if (input_fd->fd != STDIN_FILENO)
			close_fd(input_fd);
	}
}

void	set_input_output(t_cmd2 *cmd)
{
	t_cmd2 *prev;
	t_cmd2 *next;

	cmd_check(cmd);
	prev = get_previous_cmd(cmd);
	next = get_next_cmd(cmd);
	if (cmd->execution->redirections)
	{
		handle_redir_input(cmd);
		handle_redir_output(cmd);
	}
	if (prev && prev->execution->operation == PIPE_)
		handle_pipe_input(cmd);
	if (next && cmd->execution->operation == PIPE_)
		handle_pipe_output(cmd);
}