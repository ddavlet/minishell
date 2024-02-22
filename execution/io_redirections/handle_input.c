#include "../execution.h"

int	handle_input_redirection(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		msg_error("open");
	return (fd);
}
