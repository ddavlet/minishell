#include "../execution.h"

t_fd_state	*truncate_redirection(const char *file_name)
{
	int	        fd;
    t_fd_state  *fd_state;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		msg_error("open");
    fd_state = initialize_fd_state(fd);
    if (!fd_state)
    {
        close(fd);
        ft_putendl_fd("truncate redirection failed", 2);
    }
	return (fd_state);
}
