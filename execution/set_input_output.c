#include "execution.h"

void	handle_pipe_output(t_executor *exec)
{
	t_pipe	*pipe;

	pipe = next_pipe(exec->pipes);
	if (dup2(pipe->write->fd, STDOUT_FILENO) == -1)
		terminate(exec, EXIT_FAILURE,
			"minishell: unable to set pipe to output");
	close_fd(exec, pipe->write);
}

void	handle_redir_output(t_executor *exec)
{
	t_fd_state	*output_fd;

	output_fd = last_output_redir(exec);
	if (output_fd)
	{
        if (dup2(output_fd->fd, STDOUT_FILENO) == -1)
            terminate(exec, EXIT_FAILURE,
                "minishell: unable to set output");
		if (output_fd->fd != STDOUT_FILENO)
			close_fd(exec, output_fd);
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

void	handle_redir_input(t_executor *exec)
{
	t_fd_state	*input_fd;

	input_fd = last_input_redir(exec);
	if (input_fd)
	{
        if (dup2(input_fd->fd, STDIN_FILENO) == -1)
            terminate(exec, EXIT_FAILURE,
                "minishell: unable to set pipe to output");
		if (input_fd->fd != STDIN_FILENO)
			close_fd(exec, input_fd);
	}
}

void	set_input_output(t_executor *exec)
{
	t_cmd *cmd;
	t_cmd *prev;
	t_cmd *next;

	cmd = get_current_cmd(exec);
	prev = get_previous_cmd(exec, cmd);
	next = get_cmd(exec, cmd);
    if (cmd->redirs)
    {
		handle_redir_input(exec);
        handle_redir_output(exec);
    }
	if (prev && prev->operat == PIPE)
        handle_pipe_input(exec);
	if (next && cmd->operat == PIPE)
        handle_pipe_output(exec);
}