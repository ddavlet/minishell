#include "parsing.h"

// static uint32_t	ft_counter(const char **s)
// {
// 	uint32_t	i;
// 	uint32_t	count;

// 	i = 1;
// 	count = 1;
// 	while (s[i])
// 	{
// 		if (s[i][0] == 0)
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

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
		if (arr[i + 1] && arr[i][0] != 0 && arr[i + 1][0] != 0
			&& !oper_type(arr[i]) && !oper_type(arr[i + 1])
			&& !ft_isrediraction(arr[i]))
		{
			tmp = ft_strjoin(arr[i], arr[i + 1]);
			arr = realoc_merge(arr, tmp, i);
		}
		else
			i++;
	}
	return (arr);
}


