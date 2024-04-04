#include "../parsing2.h"

t_token	*get_final_token(t_token *token)
{
	while (token)
	{
		if (is_and_or_token(token) || is_pipe_token(token))
			return (token);
		if (token->next == NULL)
			return (token);
		token = token->next;
	}
    return (token);
}
