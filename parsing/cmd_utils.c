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
	// ssize_t	j;

	i = prev - 1;
	// j = 0;
	argv = (char **)ft_calloc(sizeof(char *), 1); // protect
	while (++i < next || (tokens[i] && ft_isexeption(tokens[i][0])))
	{
		if (ft_isrediraction(tokens[i]))
		{
			if (sytax_redir(tokens[++i])) // EDGE CASES HANDLER
			{
				terminate_ptr_str(argv);
				return (error_near_tocken(tokens[i])); // catch! MORE ERRORS? EDGE CASES
			}
		}
		else if (oper_type(tokens[i]))
			break ;
		else
			argv = append_arr_str(argv, ft_strdup(tokens[i]));
	}
	return (argv);
}
