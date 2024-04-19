/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:07 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 14:17:52 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_redirection_token(t_token *token)
{
	if (!token)
		return (0);
	if (ft_strncmp(token->literal, "<", ft_strlen("<")) == 0
		|| ft_strncmp(token->literal, ">", ft_strlen(">")) == 0
		|| ft_strncmp(token->literal, "<<", ft_strlen("<<")) == 0
		|| ft_strncmp(token->literal, ">>", ft_strlen(">>")) == 0)
		return (1);
	return (0);
}

int	is_redirection_token_without_name(t_token *token)
{
	if (is_redirection_token(token) && (ft_strlen(token->literal) == 1
			|| (ft_strlen(token->literal) == 2
				&& (token->literal[0] == token->literal[1]))))
		return (1);
	return (0);
}
