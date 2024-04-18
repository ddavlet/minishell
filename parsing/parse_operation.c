/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:30:46 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 14:12:36 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_operation(t_oper2 *ptr_operation, t_token *end)
{
	int	n;

	if (!end)
		return (-1);
	if (is_pipe_token(end))
		*ptr_operation = PIPE_;
	if (is_logic_operation_token(end))
	{
		n = ft_strlen(end->literal) + 1;
		if (ft_strncmp(end->literal, "&&", n) == 0)
			*ptr_operation = AND_;
		else
			*ptr_operation = OR_;
	}
	return (0);
}
