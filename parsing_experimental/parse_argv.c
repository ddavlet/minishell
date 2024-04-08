#include "parsing2.h"

int	get_argc(t_token *start, t_token *end)
{
	t_token	*token;
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

const char	*get_argument(const char *literal)
{
	char	*arg;

	arg = NULL;
	if (!ft_strchr(literal, '\'') && !ft_strchr(literal, '\"'))
		arg = ft_strdup(literal);
	else
	 	arg = merge_quotations_(literal);
	if (!arg)
		return (NULL);
    return ((const char *)arg);
}

char	**add_argument(char ***ptr_argv, t_token *token, int i)
{
	if (!ptr_argv)
		return (NULL);
	if (!token)
	{
		free_argv((const char **)*ptr_argv);
		return (NULL);
	}
	(*ptr_argv)[i] = (char *)get_argument(token->literal);
	if (!(*ptr_argv)[i])
	{
		free_argv((const char **)*ptr_argv);
		return (NULL);
	}
	return (*ptr_argv);
}

int	parse_argv(char ***ptr_argv, t_token *start, t_token *end)
{
	int		argc;
	int		i;
	t_token	*token;

	argc = get_argc(start, end);
	*ptr_argv = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!*ptr_argv)
		return (-1);
	i = 0;
	token = start;
	while (token != end->next && i < argc)
	{
		if (is_argv_token(token))
			if (add_argument(ptr_argv, token, (i++)) == NULL)
				return (-1);
		token = token->next;
	}
	return (0);
}
