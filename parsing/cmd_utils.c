#include "parsing.h"

char	**create_argv(char **tokens)
{
	char	**argv;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tokens[i] && !(ft_isexeption(tokens[i][1]) && tokens[i][0] == '\\'))
	{
		if (ft_isrediraction(tokens[i++]))
		{
			if (ft_isexeption(tokens[i][1]) && tokens[i][0] == '\\')
				return (error_near_tocken(tokens[i])); // catch!
			else
				j += 2;
		}
		i++;
	}
	argv = (char **)ft_calloc(sizeof(char *), i - j + 1); // protect
	i = 0;
	j = 0;
	while (tokens[i] && !(ft_isexeption(tokens[i][1]) && tokens[i][0] == '\\'))
	{
		if (!ft_strncmp(tokens[i], "", 2))
			i++;
		else if (ft_isrediraction(tokens[i]))
			i += 2;
		else
			argv[j++] = ft_strdup(tokens[i++]);
	}
	argv[j] = NULL;
	return (argv);
}
