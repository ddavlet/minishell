#include "parsing.h"

static int	check_merge(char **arr, ssize_t i)
{
	if (arr[i + 1] && arr[i][0] != 0 && arr[i + 1][0] != 0)
		if (!oper_type(arr[i]) && !oper_type(arr[i + 1]))
			if (!parenth_type(arr[i]) && !parenth_type(arr[i + 1]))
				if (!ft_isredir(arr[i]))
					return (1);
	return (0);
}

char	**realoc_merge(char **arr, char *new, ssize_t i)
{
	char	**new_arr;
	ssize_t	j;

	j = -1;
	new_arr = (char **)ft_calloc(sizeof(char *), ft_arr_len(arr));
	while (++j < i)
		new_arr[j] = ft_strdup(arr[j]);
	new_arr[j] = new;
	i++;
	while (arr[++i])
		new_arr[++j] = ft_strdup(arr[i]);
	terminate_ptr_str(arr);
	return (new_arr);
}

char	**pars_merge(char **arr)
{
	char	*tmp;
	ssize_t	i;

	i = 0;
	while (arr[i])
	{
		if (check_merge(arr, i))
		{
			tmp = ft_strjoin(arr[i], arr[i + 1]);
			arr = realoc_merge(arr, tmp, i);
		}
		else
			i++;
	}
	return (arr);
}


