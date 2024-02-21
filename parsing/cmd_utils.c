#include "parsing.h"

ssize_t	find_next_cmd(char **tokens, ssize_t i)
{
	if (i == 1)
		i--;
	while (!oper_type(tokens[i]))
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
	ssize_t	j;

	i = prev;
	j = 0;
	while (i < next)
	{
		if (ft_isrediraction(tokens[i++]))
		{
			if (oper_type(tokens[i]))
				return (error_near_tocken(tokens[i])); // catch!
			else
				j += 2;
		}
	}
	argv = (char **)ft_calloc(sizeof(char *), i - j + 1); // protect
	i = prev;
	j = 0;
	while (i < next)
	{
		if (ft_isrediraction(tokens[i]))
			i += 2;
		else
			argv[j++] = ft_strdup(tokens[i++]);
	}
	return (argv);
}
