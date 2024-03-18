#include "../../parsing.h"
#include "../rickroll.h"

static int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

static char	*process_trimming(char *token)
{
	char	*new;

	if (token[0] == '\"')
	{
		new = ft_strtrim(token, "\"");
		if (!new)
			return (NULL);
	}
	else if (token[0] == '\'')
	{
		new = ft_strtrim(token, "\'");
		if (!new)
			return (NULL);
	}
	else
	{
		new = ft_strdup(token);
		if (!new)
			return (NULL);
	}
	return (new);
}

char	**trim_quotes(char **arr)
{
	char	**result;
	int		count;
	int		i;

	count = arr_len(arr);
	result = ft_calloc((count + 1), sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		result[i] = process_trimming(arr[i]);
		if (!result[i])
		{
			free_2d_arr(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
