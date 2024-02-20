#include "parsing.h"

void    free_3d_arr(char ***arr)
{
    int    i;
    int    j;

    i = 0;
    while (arr[i])
    {
        j = 0;
        while (arr[i][j])
            free(arr[i][j++]);
        free(arr[i]);
        i++;
    }
    free(arr);
}

void    free_2d_arr(char **arr)
{
    int    i;

    i = 0;
    while (arr[i])
        free(arr[i++]);
    free(arr);
}

char **trimmed_copy(char **tokens)
{
	char	**new;
	int		i;

	i = 0;
	while (tokens[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '\"')
        {
			new[i] = ft_strtrim(tokens[i], "\"");
            if (!new[i])
            {
                free_2d_arr(new);
                return (NULL);
            }
        }
		else if (tokens[i][0] == '\'')
        {
			new[i] = ft_strtrim(tokens[i], "\'");
            if (!new[i])
            {
                free_2d_arr(new);
                return (NULL);
            }
        }
        else
        {
            new[i] = ft_strdup(tokens[i]);
            if (!new[i])
            {
                free_2d_arr(new);
                return (NULL);
            }
        }
		i++;
	}
	new[i] = NULL;
	return (new);
}

char    ***split_arr(char **str, char c)
{
    char    ***new;
    int        delimiter_count;
    int        i;
    int        j;
    int        k;
    int        n;
    
    i = 0;
    delimiter_count = 0;
    while (str[i])
    {
        if (ft_strncmp(str[i], "", 1) == 0)
            delimiter_count++;
        i++;
    }
    new = ft_calloc((delimiter_count + 2), sizeof(char **));
    if (!new)
        return (NULL);
    i = 0;
    j = 0;
    n = 0;
    while (i < delimiter_count + 1)
    {
        k = 0;
        while (str[n] && ft_strncmp(str[n], "", 1) != 0)
        {
            n++;
            k++;
        }
        new[i] = ft_calloc((k + 1), sizeof(char *));
        if (!new[i])
        {
            free_3d_arr(new);
            return (NULL);
        }
        n -= k;
        k = 0;
        j = 0;
        while (str[n] && ft_strncmp(str[n], "", 1) != 0)
        {
            new[i][j] = ft_strdup(str[n++]);
            if (!new[i][j])
            {
                free_3d_arr(new);
                return (NULL);
            }
            j++;
        }
        new[i++][j] = NULL;
        n++;
    }
    return (new);
}

char	*join_arr(char **arr)
{
    char	*new;
    int		i;
    int		j;
    int		k;

    i = 0;
    j = 0;
    while (arr[i])
    {
        j += ft_strlen(arr[i]);
        i++;
    }
    new = malloc(sizeof(char) * (j + 1));
    if (!new)
        return (NULL);
    i = 0;
    j = 0;
    while (arr[i])
    {
        k = 0;
        while (arr[i][k])
        {
            new[j] = arr[i][k];
            j++;
            k++;
        }
        i++;
    }
    new[j] = '\0';
    return (new);

}

#include <sys/wait.h>
int main(void)
{
    char *tokens[] = {"'e'", "ch", "'o'", "", "'test: \"thisistext\"'", NULL};
    char ***tmp_split;
    char **new_tokens;
    char **trimmed;
    char *joined_str;

    trimmed = trimmed_copy(tokens);
    tmp_split = split_arr(trimmed, '\0');
    free(trimmed);
    if (!tmp_split)
        return (1);
    int i = 0;
    while (tmp_split[i])
        i++;
    new_tokens = calloc((i + 1), sizeof(char *));
    while (i > 0)
    {
        i--;
        joined_str = join_arr(tmp_split[i]);
        if (!joined_str)
        {
            free_3d_arr(tmp_split);
            return (1);
        }
        new_tokens[i] = joined_str;
    }
    wait(NULL);
    return (0);
}