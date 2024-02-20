#include "parsing.h"

int	ft_isexeption(char c)
{
	if (c == '|') // add more exeptions if needed
		return (1);
	if (c == '&')
		return (2);
	return (0);
}

int	ft_isrediraction(const char *redir)
{
	if (ft_strncmp(redir, "<", 2))
		return (RED_INP);
	else if (ft_strncmp(redir, ">", 2))
		return (RED_OUT);
	else if (ft_strncmp(redir, "<<", 2))
		return (HEAR_DOC);
	else if (ft_strncmp(redir, ">>", 2))
		return (APP_OUT);
	else
		return (NO_REDIR);
}

t_quote	ft_isquotation(char c)
{
	if (c == '\'')
		return (SIGNLE_Q);
	if (c == '\"')
		return (DOUBLE_Q);
	return (ZERO_Q);
}

int	if_isspecchar(char c) // ??
{
	if (c == '$')
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	return (0);
}

uint32_t	del_pos(const char *txt)
{
	uint32_t	i;

	i = 0;
	while (txt[i])
	{
		if (!ft_isalnum(txt[i]) && txt[i] != '_')
			break ;
		i++;
	}
	return (i);
}
