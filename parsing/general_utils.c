#include "parsing.h"

ssize_t	ft_commandlen(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i] || !oper_type(tokens[i]))
		i++;
	return (i);
}

char	**add_escape(char **token)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (token[i])
	{
		if (ft_isexeption(token[i]) || ft_isredir(token[i])
			|| ft_isparenthesis(token[i]))
		{
			tmp = token[i];
			token[i] = ft_strjoin("\\", tmp);
			if (!token[i])
				return (NULL); //protect
			free(tmp);
		}
		i++;
	}
	return (token);
}

ssize_t	arrlen_nosspace(char **arr)
{
	ssize_t	i;
	ssize_t	j;

	if (!arr)
		return (-1);
	i = 0;
	j = 0;
	while (arr[i])
	{
		if (arr[i][0])
			j++;
		i++;
	}
	return (j);

}
