#include "parsing.h"

t_oper	oper_type(char *txt)
{
	if (ft_strncmp(txt, "|", 2))
		return (PIPE);
	if (ft_strncmp(txt, "||", 3))
		return (OR);
	if (ft_strncmp(txt, "&&", 3))
		return (AND);
	else
		return (RUN);
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
