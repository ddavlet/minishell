#include "../execution.h"

void	close_pipe(t_pipe *pipe)
{
    if (pipe)
    {
        if (pipe->read->is_open)
            close_fd(pipe->read);
        if (pipe->write->is_open)
            close_fd(pipe->write);
        free(pipe->pipe_fd);
        free(pipe->read);
        free(pipe->write);
        free(pipe);
    }
}