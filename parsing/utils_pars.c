#include "parsing.h"

int	ft_isexeption(char c)
{
	if (c == '|') // add more exeptions if needed
		return (1);
	if (c == '&')
		return (2);
	return (0);
}

t_quote	ft_isquotation(char c)
{
	if (c == '\'')
		return (SIGNLE_Q);
	if (c == '\"')
		return (DOUBLE_Q);
	return (ZERO_Q);
}

int	if_isspecchar(char c)
{
	if (c == '$')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	return (0);
}
