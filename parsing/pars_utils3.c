#include "parsing.h"

t_oper	oper_type(char *txt)
{
	if (!ft_strncmp(txt, "\\|", 3))
		return (PIPE);
	if (!ft_strncmp(txt, "\\||", 4))
		return (OR);
	if (!ft_strncmp(txt, "\\&&", 4))
		return (AND);
	else
		return (RUN);
}

void	trim_quotes(char **tokens)
{
	ssize_t	i;
	char	*tmp;

	i = 0;
	while (tokens[i])
	{
		tmp = tokens[i];
		if (tokens[i][0] == '\'')
			tokens[i] = ft_strtrim(tmp, "'");
		else if (tokens[i][0] == '\"')
			tokens[i] = ft_strtrim(tmp, "\"");
		else
			tmp = NULL;
		free (tmp);
		i++;
	}
}

char	**parse_delspace(char **tokens)
{
	ssize_t	i;
	ssize_t	j;
	char	**new_arr;

	i = 0;
	j = 0;
	new_arr = (char **)ft_calloc(sizeof(char *), (ft_arr_len(tokens) + 1));
	while (tokens[i])
	{
		if (tokens[i][0] == 0)
			i++;
		else
			new_arr[j++] = ft_strdup(tokens[i++]);
	}
	terminate_ptr_str(tokens);
	return (new_arr);
}
