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

#include "parsing.h"

// static int	check_quotations(t_token *tokens)
// {
// 	t_token		*tmp;
// 	uint32_t	i;
// 	long		j;
// 	int			quot_type;

// 	tmp = tokens;
// 	i = 0;
// 	quot_type = 0;
// 	while (tmp)
// 	{
// 		j = -1;
// 		while (tmp->literal[++j])
// 		{
// 			if (quot_type && tmp->literal[j] != quot_type)
// 				;
// 			else if (quot_type)
// 				quot_type = 0;
// 			else if (tmp->literal[j] == '\'')
// 				quot_type = '\'';
// 			else if (tmp->literal[j] == '\"')
// 				quot_type = '\"';
// 		}
// 		if (quot_type)
// 			return (1);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

int	syntax_error(const char *token_name)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(token_name, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (-1);
}

int	unclosed_quotations(t_token *token)
{
	const char	*opening;
	const char	*closing;

	if (!contains_quotations(token->literal))
		return (0);
	opening = get_opening_quote(token->literal);
	while (opening)
	{
		closing = get_closing_quote(opening + 1, opening);
		while (closing && *(closing - 1) == '\\')
			closing = get_closing_quote(closing + 1, opening);
		if (!closing)
			return (1);
		opening = get_opening_quote(closing + 1);
	}
	return (0);
}

int	unclosed_escape(t_token *token)
{
	const char	*backslash;

	backslash = ft_strchr(token->literal, '\\');
	if (backslash && !is_escaped(backslash, token->literal) && *(backslash + 1) == '\0')
		return (1);
	return (0);
}

int	syntax_check(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	if (ft_strncmp(token->literal, "", 1) == 0)
		return (-1);
	if (is_operation_token(token))
		return (syntax_error(token->literal));
	token = token->next;
	while (token)
	{
		if (unclosed_escape(token))
			return (syntax_error(token->literal));
		if (unclosed_quotations(token))
			return (syntax_error(token->literal));
		if (is_operation_token(token) && is_operation_token(token->next))
			return (syntax_error(token->next->literal));
		if (is_operation_token(token) && !token->next)
			return (syntax_error(token->literal));
		if (is_redirection_token(token) && (is_redirection_token(token->next)
				|| is_operation_token(token->next)))
			return (syntax_error(token->next->literal));
		if (is_redirection_token(token) && !token->next)
			return (syntax_error(token->literal));
		token = token->next;
	}
	return (0);
}
