#include "parsing.h"

ssize_t	ft_commandlen(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i] || !oper_type(tokens[i]))
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
		if (ft_isexeption(token[i]))
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

ssize_t	ft_arr_len(char **arr) // calculates only without spaces
{
	ssize_t	i;

	if (!arr)
		return (-1);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**append_arr_str(char **arr, char *str)
{
	char	**new_arr;
	ssize_t	i;

	i = -1;
	new_arr = (char **)ft_calloc(sizeof(char *), ft_arr_len(arr) + 2);
	while (arr[++i])
		new_arr[i] = arr[i];
	new_arr[i] = str;
	free(arr);
	return (new_arr);
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
