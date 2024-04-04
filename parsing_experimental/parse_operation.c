#include "parsing2.h"

t_oper2	parse_operation(t_token *end)
{
    int n;

	if (!end)
	{
		ft_putendl_fd("token missing", STDERR_FILENO);
		return (NOTHING);
	}
	if (is_pipe_token(end))
		return (PIPE_);
	if (is_logic_token(end))
	{
        n = ft_strlen(end->literal) + 1;
		if (ft_strncmp(end->literal, "&&", n) == 0)
			return (AND_);
		else
			return (OR_);
	}
	return (NOTHING);
}
