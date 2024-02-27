#include "../../parsing.h"
#include "../rickroll.h"

static int	calculate_total_length(char **arr)
{
	int	i;
	int	j;
	int	total_length;

	i = 0;
	j = 0;
	total_length = 0;
	while (arr[i])
	{
		j += ft_strlen(arr[i]);
		i++;
	}
	return (total_length);
}

static char	*concatenate(char *dst_str, char **src_arr)
{
	int	i;
	int	j;
	int	k;

	if (!src_arr)
	{
		dst_str[0] = '\0';
		return (dst_str);
	}
	i = 0;
	j = 0;
	while (src_arr[i])
	{
		k = 0;
		while (src_arr[i][k])
			dst_str[j++] = src_arr[i][k++];
		i++;
	}
	dst_str[j] = '\0';
	return (dst_str);
}

char	*join_array_elements(char **arr)
{
	int		total_length;
	char	*result;

	total_length = calculate_total_length(arr);
	result = (char *)ft_calloc(total_length + 1, sizeof(char));
	if (!result)
		return (NULL);
	concatenate(result, arr);
	return (result);
}
