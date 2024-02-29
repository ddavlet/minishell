#include "parsing.h"

t_oper	oper_type(char *txt)
{
	if (!txt)
		return (RUN);
	if (!ft_strncmp(txt, "\\||", 4))
		return (OR);
	if (!ft_strncmp(txt, "\\&&", 4))
		return (AND);
	if (!ft_strncmp(txt, "\\|", 3))
		return (PIPE);
	if (!ft_strncmp(txt, "\\&", 3))
		return (BCKGR);
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
	new_arr = (char **)ft_calloc(sizeof(char *), (arrlen_nosspace(tokens) + 1));
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

int	ft_isparenthesis(char *txt)
{
	if (!ft_strncmp(txt, "(", 2))
		return (1);
	if (!ft_strncmp(txt, ")", 2))
		return (2);
	else
		return (0);
}

int	count_brackets(char **arr)
{
	ssize_t	count;
	ssize_t	i;

	i = 0;
	count = 0;
	while (arr[i])
	{
		if (ft_isparenthesis(arr[i]) == 1)
			count++;
		else if (ft_isparenthesis(arr[i]) == 2)
			count--;
		i++;
	}
	if (count < 0)
	{
		error_near_tocken(")");
		return (1);
	}
	else if (count > 0)
	{
		error_near_tocken("(");
		return (1);
	}
	else
		return (0);
}
