#include "parsing.h"

ssize_t	ft_commandlen(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i] || !(ft_isexeption(tokens[i][1]) && tokens[i][0] == '\\'))
		i++;
	return (i);
}

char	**add_escape(char **token, const char *esc)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (token[i])
	{
		if (ft_isexeption(token[i][0]))
		{
			tmp = token[i];
			token[i] = ft_strjoin(esc, tmp);
			if (!token[i])
				return (NULL); //protect
			free(tmp);
		}
		i++;
	}
	return (token);
}

ssize_t	ft_arr_len(char **arr)
{
	ssize_t	i;

	if (!arr)
		return (-1);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
