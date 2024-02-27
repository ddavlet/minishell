#include "../execution/execution.h"

int init_fd_state(t_fd_state *fd_state, int fd, char *purpose)
{
    if (!fd_state)
        return (-1);
    fd_state->fd = fd;
    fd_state->is_open = 0;
    fd_state->purpose = purpose;
    return (0);
}

t_pipe *create_pipe(void)
{
    int *pipe_fd;
    t_pipe  *pipe;

    if (!pipe_fd)
        return (NULL);
    pipe_fd = ft_calloc(2, sizeof(int));
    pipe = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
    if (!pipe)
    {
        free(pipe_fd);
        return (NULL);
    }
    pipe->pipe_fd = pipe_fd;

    if (pipe(pipe_fd) == -1)
    {
        free(pipe_fd);
        free(pipe);
        return (NULL);
    }
    return (pipe_fd);
}

t_pipe  **init_pipe_stack(t_executor *exec)
{
    t_pipe **stack;

    stack = (t_pipe **)ft_calloc(pipe_stack_size(exec), sizeof(t_pipe *));
    if (!stack)
        return (NULL);
    exec->pipe_stack = stack;
    return (stack);
}