#include "../execution.h"

void    close_redir(t_fd_state *fd_state)
{
	if (fd_state)
    {
        if (fd_state->pipe)
            close_pipe(fd_state->pipe);
		else
			close_fd(fd_state);
    }
}

