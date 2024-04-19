/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_logic_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:53 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:28:54 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_logic_operation_token(t_token *token)
{
	if (!token)
	{
		ft_putendl_fd("missing token", STDERR_FILENO);
		return (0);
	}
	if (ft_strncmp(token->literal, "&&", ft_strlen(token->literal) + 1) == 0
		|| ft_strncmp(token->literal, "||", ft_strlen(token->literal) + 1) == 0)
		return (1);
	return (0);
}
