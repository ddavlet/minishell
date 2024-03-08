#include "../execution.h"

t_fd_state	*input_redirection(const char *file_name)
{
	int	        fd;
    t_fd_state  *fd_state;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		msg_error("open");
    fd_state = initialize_fd_state(fd);
    if (!fd_state)
    {
        close(fd);
        terminate(NULL, NULL, EXIT_FAILURE, "input redirection failure");
    }
	return (fd_state);
}
