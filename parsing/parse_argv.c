/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:30:37 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:30:37 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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
		if (is_redirection_token_without_name(token))
			token = token->next->next;
		else
			token = token->next;
	}
	return (argc);
}

int	add_argument(char **ptr_argument, char **argv, t_token *token)
{
    *ptr_argument = ft_strdup(token->literal);
    if (!*ptr_argument)
    {
		free_argv((const char **)argv);
		return (-1);
	}
	return (0);
}

int parse_argv(char ***ptr_argv, t_token *start, t_token *end)
{
	int		argc;
	int		i;
    char    **argv_new;
	t_token	*token;

	argc = get_argc(start, end);
	argv_new = (char **)ft_calloc(argc + 1, sizeof(char *));
	if (!argv_new)
		return (-1);
	i = 0;
	token = start;
	while (token != end->next && i < argc)
	{
		if (is_argv_token(token))
			if (add_argument(&(argv_new[i++]), argv_new, token) == -1)
				return (-1);
        if (is_redirection_token_without_name(token))
            token = token->next->next;
		else
			token = token->next;
	}
    *ptr_argv = argv_new;
	return (0);
}
