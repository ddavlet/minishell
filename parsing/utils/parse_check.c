/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:19 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/27 14:31:35 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	check_quotations(t_token *tokens)
{
	t_token		*tmp;
	uint32_t	i;
	long		j;
	int			quot_type;

	tmp = tokens;
	i = 0;
	quot_type = 0;
	while (tmp)
	{
		j = -1;
		while (tmp->literal[++j])
		{
			if (quot_type && tmp->literal[j] != quot_type)
				;
			else if (quot_type)
				quot_type = 0;
			else if (tmp->literal[j] == '\'')
				quot_type = '\'';
			else if (tmp->literal[j] == '\"')
				quot_type = '\"';
		}
		if (quot_type)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static int	syntax_check(t_token *tokens)
{
	t_token	*tmp;
	t_token	*first;

	first = tokens;
	if (is_operation_token(first))
		return (syntax_error(first->literal));
	tmp = first;
	while (tmp)
	{
		if (is_operation_token(tmp) && is_operation_token(tmp->next))
			return (syntax_error(tmp->next->literal));
		if (is_operation_token(tmp) && !tmp->next)
			return (syntax_error(tmp->literal));
		if (is_redirection_token(tmp) && (is_redirection_token(tmp->next)
				|| is_operation_token(tmp->next)))
			return (syntax_error(tmp->next->literal));
		if (is_redirection_token(tmp) && !tmp->next)
			return (syntax_error(tmp->literal));
		tmp = tmp->next;
	}
	return (0);
}

int	parse_check(t_token *tokens)
{
	if (!tokens->literal[0])
		return (1);
	if (check_quotations(tokens))
	{
		write(2, "minishell: unclosed quotations are not supported\n", 49);
		return (1);
	}
	return (syntax_check(tokens));
}
