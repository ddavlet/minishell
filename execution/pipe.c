#include "../execution/execution.h"

int	init_fd_state(t_fd_state *fd_state, int fd, char *purpose)
{
	if (!fd_state)
		return (-1);
	fd_state->fd = fd;
	fd_state->is_open = 0;
	fd_state->purpose = purpose;
	return (0);
}

t_pipe	*create_pipe(void)
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
	p->pipe_fd = pipe_fd;
	if (pipe(p->pipe_fd) == -1)
	{
		free(pipe_fd);
		free(p);
		return (NULL);
	}
	return (p);
}
