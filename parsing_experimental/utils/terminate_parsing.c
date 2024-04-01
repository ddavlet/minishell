#include "../parsing2.h"

void	terminate_parsing(const char *line, t_cmd2 *cmds, t_token *tokens,
		char *msg)
{
    free_cmds(cmds);
	free_tokens(tokens);
	free((char *)line);
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
