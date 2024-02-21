#include "../parsing.h"
#include "rickroll.h"

char	**join_strings_in_each_array(char ***arr_3d)
{
	int		i;
	char	**arr_2d;

	i = 0;
	while (arr_3d[i])
		i++;
	arr_2d = (char **)calloc(i + 1, sizeof(char *));
	if (!arr_2d)
	{
		free_3d_arr(arr_3d);
		return (NULL);
	}
	while (--i >= 0)
		arr_2d[i] = join_array_elements(arr_3d[i]);
	return (arr_2d);
}

char	**remove_quotes_and_join(char **arr)
{
	char	**trimmed;
	char	***split;
	char	**new_arr;
	char	*joined_str;
	int		i;

	trimmed = trim_quotes(arr);
	if (!trimmed)
		return (NULL);
	split = split_arr(trimmed, "\0");
	free_2d_arr(trimmed);
	if (!split)
		return (NULL);
	new_arr = join_strings_in_each_array(split);
	return (new_arr);
}

#include <sys/wait.h>

int	main(void)
{
	char *tokens[] = {"'e'", "ch", "'o'", "", "'test: \"thisistext\"'", NULL};
	char **new_tokens;

	new_tokens = remove_quotes_and_join(tokens);
	if (!new_tokens)
	{
		printf("Error\n");
		return (1);
	}
	int i = 0;
	while(new_tokens[i])
	{
		printf("%s\n", new_tokens[i]);
		i++;
	}
	return (0);
}