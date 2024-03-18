#include "../execution/execution.h"

t_fd_state	*initialize_fd_state(int fd)
{
    t_fd_state  *fd_state;

    fd_state = (t_fd_state *)ft_calloc(1, sizeof(t_fd_state));
	if (!fd_state)
		return (NULL);
	fd_state->fd = fd;
	fd_state->is_open = 1;
	return (fd_state);
}

static t_pipe  *initialize_pipe(void)
{
	int		*pipe_fd;
	t_pipe	*p;

    pipe_fd = ft_calloc(2, sizeof(int));
	if (!pipe_fd)
		return (NULL);
	p = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!p)
	{
		free(pipe_fd);
		return (NULL);
	}    
	if (pipe(pipe_fd) == -1)
	{
		free(pipe_fd);
		return (NULL);
	}
	p->pipe_fd = pipe_fd;
	return (p);
}

t_pipe	*create_pipe(void)
{
	t_pipe	*pipe;

    pipe = initialize_pipe();
	if (!pipe)
		return(NULL);
	pipe->read = initialize_fd_state(pipe->pipe_fd[0]);
	if (!(pipe->read))
	{
		free(pipe);
		return (NULL);
	}
	pipe->write = initialize_fd_state(pipe->pipe_fd[1]);
	if (!(pipe->write))
	{
		free (pipe->read);
		free (pipe);
		return (NULL);
	}
	return (pipe);
}

// void    close_pipe(t_pipe *pipe)
// {
//     if (!pipe || !pipe->write || !pipe->read)
//         terminate(NULL, EXIT_FAILURE, "Failed to close pipe.");
//     if (pipe->write->is_open)
//         close_fd(pipe->write);
//     if (pipe->read->is_open)
//         close_fd(pipe->read);
// }

t_pipe	*get_next_pipe(t_executor *exec)
{
	debug_started("get_next_pipe");

    t_pipe  *pipe;
    int     i;

    i = 0;
    while(exec->pipes[i] && exec->pipes[i]->write->is_open == 0)
        i++;
    pipe = exec->pipes[i];
	debug_pipe_information(pipe);
	debug_ended("get_next_pipe");
	return (pipe);	
}

void    close_next_pipe(t_executor *exec)
{
	debug_started("close_next_pipe");

    t_pipe  *pipe;
    int     i;

    i = 0;
    while(exec->pipes[i] && exec->pipes[i]->write->is_open == 0)
        i++;
    pipe = exec->pipes[i];

	close_fd(pipe->write);
	debug_pipe_information(pipe);
	debug_ended("close_next_pipe");
}

t_pipe **initialize_pipes(t_executor *exec)
{
	int		pipe_count;
	t_pipe **pipes;

	pipe_count = count_pipes(exec, false);
	pipes = (t_pipe **)ft_calloc(pipe_count, sizeof(t_pipe *));
	if (!pipes)
		return (NULL);
	while (pipe_count--)
		pipes[pipe_count] = create_pipe();
	return (pipes);
}