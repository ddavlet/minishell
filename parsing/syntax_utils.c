#include "parsing.h"

int	sytax_redir(char *token) // to check what goes after redirection < > << >>
{
	if (ft_isrediraction(token))
		return (1);
	else if (oper_type(token))
		return (2);
	else
		return (0);
}

int	syntax_exeption(char *token) // to check what goes after exeption | || &&
{
	if (oper_type(token))
		return (1);
	else
		return (0);
}
