#include "../execution.h"

int	handle_append_redirection(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		msg_error("open");
	return (fd);
}
