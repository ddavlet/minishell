#include "../parsing2.h"

int	is_argv_token(t_token *token)
{
	if (!token)
	{
		ft_putendl_fd("missing token", STDERR_FILENO);
		return (0);
	}
	if (!is_redirection_token(token) && !is_pipe_token(token)
		&& !is_and_or_token(token))
		return (1);
	return (0);
}