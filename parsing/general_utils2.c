#include "parsing.h"

char	**inject_string(char **to_arr, char **from_arr, ssize_t inj_indx)
{
	char **new_arr;
	ssize_t	to_indx;
	ssize_t	indx;

	indx = -1;
	to_indx = 0;
	if (!from_arr)
		return (to_arr);
	if (!to_arr)
		return (NULL);  // catch
	new_arr = (char **)ft_calloc(ft_arr_len(to_arr) + (ft_arr_len(from_arr) * 2 - 1), sizeof(char *));
	if (!new_arr)
		return (error_general("wildcard parsing", NULL)); // catch
	while (++indx < inj_indx)
		new_arr[indx] = to_arr[indx];
	while (from_arr[to_indx])
	{
		new_arr[indx++] = from_arr[to_indx++];
		new_arr[indx++] = ft_strdup("");
	}
	free(new_arr[indx--]);
	while (to_arr[++(inj_indx)])
		new_arr[indx++] = to_arr[inj_indx];
	new_arr[indx] = NULL;
	free(to_arr);
	*from_arr = NULL;
	return (new_arr);
}

char	**arrstr_copy(const char **envp)
{
	char		**copy_envp;
	int32_t		len;

	len = 0;
	while (envp[len])
		len++;
	copy_envp = (char **)ft_calloc(sizeof (char *), len + 1);
	len = -1;
	while (envp[++len])
		copy_envp[len] = ft_strdup(envp[len]);
	return (copy_envp);
}

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
