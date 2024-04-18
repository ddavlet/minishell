/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_argv_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:51 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:28:51 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_argv_token(t_token *token)
{
	if (!token)
	{
		ft_putendl_fd("missing token", STDERR_FILENO);
		return (0);
	}
	if (!is_redirection_token(token) && !is_pipe_token(token)
		&& !is_logic_operation_token(token))
		return (1);
	return (0);
}
