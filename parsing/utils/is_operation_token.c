/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operation_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:56 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:31:31 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_operation_token(t_token *token)
{
	if (!token)
		return (0);
	if (is_pipe_token(token))
		return (1);
	if (is_logic_operation_token(token))
		return (1);
	return (0);
}
