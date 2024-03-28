#include "parsing.h"

char	**argv_scope(char **tokens, ssize_t prev, ssize_t next)
{
	char	**argv;
	// ssize_t	i;

	// i = prev - 1;
	argv = (char **)ft_calloc(sizeof(char *), 3);
	if (!argv)
		return (NULL); //protect
	argv[0] = ft_strdup("minishell");
	argv[1] = ft_strdup("-n");
	if (!argv)
		return (NULL);
	while (prev <= next)
		argv = append_arr_str(argv, ft_strdup(tokens[prev++]));
	return (argv);
}

t_cmd	*set_scope(char **tokens, ssize_t *prev)
{
	ssize_t	i;
	int		count;
	t_cmd	*cmd;

	if (*prev == 1)
		(*prev)--;
	i = *prev;
	count = 0;
	if (parenth_type(tokens[i]) == 1)
	{
		cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
		cmd->com = ft_strdup("minishell");
		while (tokens[++i])
		{
			if (parenth_type(tokens[i]) == 2 && count == 0)
			{
				cmd->argv = argv_scope(tokens, *prev + 1, i - 1);
				*prev = i + 2;
				if (!tokens[i + 1])
					(*prev)--;
				cmd->operat = oper_type(tokens[i + 1]);
				return (cmd);
			}
			else if (parenth_type(tokens[i]) == 1)
				count++;
			else if (parenth_type(tokens[i]) == 2)
				count--;
		}
		free(cmd);
		return (NULL);
	}
	return (NULL);
}
