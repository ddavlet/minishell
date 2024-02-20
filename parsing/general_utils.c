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

// char	**ft_arr_append(char **ptr)
// {
// 	char	**new_ptr;

// 	if (!ptr)
// 		ptr =
// }
