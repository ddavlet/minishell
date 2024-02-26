#include "parsing.h"

int	ft_isignored(char *txt)
{
	if (!ft_strncmp(txt, "(", 2))
		return (1);
	if (!ft_strncmp(txt, ")", 2))
		return (1);
	if (!ft_strncmp(txt, ";", 2))
		return (1);
	if (!ft_strncmp(txt, "!", 2))
		return (1);
	if (oper_type(txt) == BCKGR)
		return (1);
	if (!ft_strncmp(txt, "\\", 2)) // 3 or 2?
	{
		write(2, "escape met, check it", 20);
		return (1);
	}
	else
		return (0);
}

int	sytax_redir(char *token) // to check what goes after redirection < > << >>
{
	if (ft_isredir(token))
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

int	syntax_ignored(char *token)
{
	if (ft_isignored(token))
		return (1);
	else
		return (0);
}

void	*check_tokens(char **tokens)
{
	ssize_t	i;

	i = 0;
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
	return (tokens);
}
