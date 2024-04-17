#include "../parsing.h"

int	is_operation_token(t_token *token)
{
	if (!token)
		return (0);
	if (is_pipe_token(token))
		return (1);
	if (is_logic_operation_token(token))
		return (1);
	return (0);
}
