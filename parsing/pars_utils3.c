#include "parsing.h"

t_oper	oper_type(char *txt)
{
	if (!txt)
		return (RUN);
	if (!ft_strncmp(txt, "\\||", 4))
		return (OR);
	if (!ft_strncmp(txt, "\\&&", 4))
		return (AND);
	if (!ft_strncmp(txt, "\\|", 3))
		return (PIPE);
	if (!ft_strncmp(txt, "\\&", 3))
		return (BCKGR);
	else
		return (RUN);
}

int	parenth_type(char *txt)
{
	if (!txt)
		return (0);
	if (!ft_strncmp(txt, "\\(", 3))
		return (1);
	if (!ft_strncmp(txt, "\\)", 3))
		return (2);
	return (0);
}

t_red_sym	redir_type(char *txt)
{
	if (!ft_strncmp(txt, "\\<<", 4))
		return (HEAR_DOC);
	else if (!ft_strncmp(txt, "\\>>", 4))
		return (APP_OUT);
	else if (!ft_strncmp(txt, "\\<", 3))
		return (RED_INP);
	else if (!ft_strncmp(txt, "\\>", 3))
		return (RED_OUT);
	else
		return (NO_REDIR);
}

void	trim_quotes(char **tokens)
{
	ssize_t	i;
	char	*tmp;

	i = 0;
	while (tokens[i])
	{
		tmp = tokens[i];
		if (tokens[i][0] == '\'')
			tokens[i] = ft_strtrim(tmp, "'");
		else if (tokens[i][0] == '\"')
			tokens[i] = ft_strtrim(tmp, "\"");
		else
			tmp = NULL;
		free (tmp);
		i++;
	}
}

int	count_parenth(char **arr)
{
	ssize_t	count;
	ssize_t	i;

	i = 0;
	count = 0;
	while (arr[i])
	{
		if (ft_isparenthesis(arr[i]) == 1)
			count++;
		else if (ft_isparenthesis(arr[i]) == 2)
			count--;
		i++;
	}
	if (count < 0)
	{
		error_near_tocken(")");
		return (1);
	}
	else if (count > 0)
	{
		error_near_tocken("(");
		return (1);
	}
	else
		return (0);
}
