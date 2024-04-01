#include "parsing2.h"

int	get_argc(t_token *start, t_token *end)
{
	t_token *token;
	int		argc;

	argc = 0;
	token = start;
	while (token != end->next)
	{
		if (is_argv_token(token))
			argc++;
		token = token->next;
	}
	return (argc);
}

char	**add_argument(char **argv, int i, t_token *token)
{
	if (!argv)
		return (NULL);
	if (!token)
	{
		free_argv(argv);
		return (NULL);
	}
	argv[i] = ft_strdup(token->literal);
	if (!argv[i])
	{
		free_argv(argv);
		return (NULL);
	}
	return (argv);
}

const char **parse_argv(t_token *start, t_token *end)
{
    char	**argv;
    int		argc;
    int		i;
    t_token	*token;

    argc = get_argc(start, end);
	argv = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
    token = start;
	while (token != end->next && i < argc)
	{
		if (is_argv_token(token))
			if (add_argument(argv, i, token) == NULL)
				return (NULL);
		start = start->next;
	}
	return ((const char **)argv);
}

