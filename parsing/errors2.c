#include "parsing.h"

void	*error_syntax(t_cmd *ptr)
{
	ft_putendl_fd("minishell: syntax error in expression", 2);
	terminate_cmd(ptr);
	return (NULL);
}
