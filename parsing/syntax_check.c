/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:19 by ddavlety          #+#    #+#             */
/*   Updated: 2024/05/01 14:56:17 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_quotations(t_token *tokens)
{
	t_token		*tmp;
	uint32_t	i;
	long		j;
	int			quot_type;

	tmp = tokens;
	i = 0;
	quot_type = 0;
	j = -1;
	while (tmp->literal[++j])
	{
		if (quot_type && tmp->literal[j] != quot_type)
			;
		else if (quot_type == tmp->literal[j])
			quot_type = 0;
		else if (tmp->literal[j] == '\'')
			quot_type = '\'';
		else if (tmp->literal[j] == '\"')
			quot_type = '\"';
	}
	if (quot_type)
		return (1);
	return (0);
}

int	syntax_error(const char *token_name)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(token_name, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (-1);
}

int	syntax_check(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	if (ft_strncmp(token->literal, "", 1) == 0)
		return (-1);
	if (is_operation_token(token))
		return (syntax_error(token->literal));
	while (token)
	{
		if (check_quotations(token))
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
