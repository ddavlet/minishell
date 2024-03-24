#include "parsing.h"

int	ft_isignored(char *txt)
{
	if (!ft_strncmp(txt, ";", 2))
		return (1);
	if (!ft_strncmp(txt, "!", 2))
		return (1);
	if (oper_type(txt) == BCKGR)
		return (1);
	if (!ft_strncmp(txt, "{", 2) || !ft_strncmp(txt, "}", 2))
		return (1);
	if (!ft_strncmp(txt, "!", 2))
		return (1);
	if (!ft_strncmp(txt, "[", 2) || !ft_strncmp(txt, "]", 2))
		return (1);
	if (!ft_strncmp(txt, "\\", 2))
		return (1);
	else
		return (0);
}

int	sytax_redir(char *token)
{
	if (ft_isredir(token))
		return (1);
	else if (oper_type(token))
		return (2);
	else
		return (0);
}

int	syntax_exeption(char *token)
{
	if (oper_type(token))
		return (1);
	else
		return (0);
}

void	*check_tokens(char **tokens)
{
	ssize_t	i;

	i = 0;
	if (!tokens[i])
		return (NULL);
	if (count_brackets(tokens))
		return (error_near_tocken("parenthesis"));
	if (!ft_strncmp(tokens[0], ")", 2))
		return (error_near_tocken(tokens[i]));
	while (tokens[i + 1])
	{
		if (ft_isignored(tokens[i])) // is ignored
			return (error_near_tocken(tokens[i]));
		if (oper_type(tokens[i]) && oper_type(tokens[i + 1]))
			return (error_near_tocken(tokens[i + 1]));
		if (ft_isredir(tokens[i]) && sytax_redir(tokens[i + 1]))
			return (error_near_tocken(tokens[i + 1]));
		i++;
	}
	if (oper_type(tokens[i]) && !tokens[i + 1])
		return (error_near_tocken(tokens[i]));
	return (tokens);
}
