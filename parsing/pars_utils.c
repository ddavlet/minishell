#include "parsing.h"

int	ft_isparenthesis(char *txt)
{
	if (!ft_strncmp(txt, "(", 2))
		return (1);
	if (!ft_strncmp(txt, ")", 2))
		return (2);
	else
		return (0);
}

t_oper	ft_isexeption(char *txt)
{
	if (!ft_strncmp(txt, "||", 2))
		return (OR);
	if (!ft_strncmp(txt, "&&", 2))
		return (AND);
	if (!ft_strncmp(txt, "|", 1))
		return (PIPE);
	if (!ft_strncmp(txt, "&", 1))
		return (BCKGR);
	else
		return (RUN);
}

t_red_sym	ft_isredir(const char *redir)
{
	if (!ft_strncmp(redir, "<<", 2))
		return (HEAR_DOC);
	else if (!ft_strncmp(redir, ">>", 2))
		return (APP_OUT);
	else if (!ft_strncmp(redir, "<", 1))
		return (RED_INP);
	else if (!ft_strncmp(redir, ">", 1))
		return (RED_OUT);
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
