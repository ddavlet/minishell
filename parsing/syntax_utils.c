#include "parsing.h"

int	sytax_redir(char *token)
{
	if (ft_isrediraction(token))
		return (1);
	else if (oper_type(token))
		return (2);
	else
		return (0);
}
