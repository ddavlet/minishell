#include "../../parsing.h"
#include "../rickroll.h"

static int	copy_segment(char ***dst, char **src, int *n, int i)
{
	int	j;

	j = 0;
	while (src[*n] && ft_strncmp(src[*n], "", 1) != 0)
	{
		dst[i][j] = ft_strdup(src[(*n)++]);
		if (!dst[i][j])
		{
			free_3d_arr(dst);
			return (-1);
		}
		j++;
	}
	dst[i][j] = NULL;
	(*n)++;
	return (0);
}

static int	count_until_delimiter(char **arr, int start)
{
	int	count;

	count = 0;
	while (arr[start + count] && ft_strncmp(arr[start + count], "", 1) != 0)
		count++;
		count++;
	return (count);
}

static char	***process_split(char ***dst_arr, char **src, int delimiter_count)
{
	int	i;
	int	n;
	int	count;

	i = 0;
	n = 0;
	while (i < delimiter_count + 1)
	{
		count = count_until_delimiter(src, n);
		dst_arr[i] = ft_calloc((count + 1), sizeof(char *));
		if (!dst_arr[i])
		{
			free_3d_arr(dst_arr);
			return (NULL);
		}
		if (copy_segment(dst_arr, src, &n, i) == -1)
			return (NULL);
		i++;
	}
	return (dst_arr);
}

char	***split_arr(char **src, char *delimiter)
{
	char	***result;
	int		delimiter_count;
	int		i;

	i = 0;
	delimiter_count = 0;
	while (src[i])
	{
		if (ft_strncmp(src[i], delimiter, 1) == 0)
			delimiter_count++;
		i++;
	}
	result = (char ***)ft_calloc((delimiter_count + 2), sizeof(char **));
	if (!result)
		return (NULL);
	result = process_split(result, src, delimiter_count);
	if (!result)
	{
		free_3d_arr(result);
		return (NULL);
	}
	return (result);
}
