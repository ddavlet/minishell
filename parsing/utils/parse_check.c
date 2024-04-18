#include "../parsing.h"

int syntax_check(t_token *tokens)
{
	t_token	*tmp;
	t_token	*first;

	first = tokens;
	if (is_operation_token(first))
		return (syntax_error(first->literal));
	tmp = first;
	while (tmp)
	{
		if (is_operation_token(tmp) && is_operation_token(tmp->next))
			return (syntax_error(tmp->next->literal));
		if (is_operation_token(tmp) && !tmp->next)
			return (syntax_error(tmp->literal));
		if (is_redirection_token(tmp) && (is_redirection_token(tmp->next)
				|| is_operation_token(tmp->next)))
			return (syntax_error(tmp->next->literal));
		if (is_redirection_token(tmp) && !tmp->next)
			return (syntax_error(tmp->literal));
		tmp = tmp->next;
	}
	return (0);
}

int	parse_check(t_token *tokens)
{

	if (!tokens->literal[0])
		return (1);
	return (syntax_check(tokens));
}
