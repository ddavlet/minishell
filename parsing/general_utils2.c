#include "parsing.h"

int	*ft_intarrdup(int *arr)
{
	int	*new_arr;
	ssize_t	i;

	i = 0;
	while (arr[i])
		i++;
	new_arr = (int *)ft_calloc(sizeof(int), i + 1);
	i = -1;
	while (arr[++i])
		new_arr[i] = arr[i];
	// free(arr);
	return (new_arr);
}

int	id_gen(int seed)
{
	seed = (1103515245 * seed + 12345) % 2147483648;
	return (seed);
}
