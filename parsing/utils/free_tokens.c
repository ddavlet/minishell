#include "../parsing.h"

void	free_tokens(t_token *tokens)
{
	t_token *tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free((char *)tokens->literal);
		free(tokens);
		tokens = tmp;
	}
}
