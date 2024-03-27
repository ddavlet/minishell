#include "parsing.h"

ssize_t	find_next_cmd(char **tokens, ssize_t i)
{
	if (i == 1)
		i--;
	while (tokens[i] && !oper_type(tokens[i]))
	{
		i++;
		if (!tokens[i])
		{
			i--;
			break ;
		}
	}
	return (i);
}

char	**create_argv(char **tokens, ssize_t prev, ssize_t next)
{
	char	**argv;
	ssize_t	i;

	i = prev - 1;
	argv = (char **)ft_calloc(sizeof(char *), 1); // protect
	if (!argv)
		return (NULL);
	while (++i < next || (tokens[i] && ft_isexeption(tokens[i])))
	{
		if (ft_isredir(tokens[i]))
			i++;
		else if (ft_isparenthesis(tokens[i]))
			;
		else if (oper_type(tokens[i]))
			break ;
		else
			argv = append_arr_str(argv, ft_strdup(tokens[i]));
	}
	return (argv);
}
