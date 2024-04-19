/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_final_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:28:48 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:28:49 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

t_token	*get_final_token(t_token *token)
{
	while (token)
	{
		if (is_logic_operation_token(token) || is_pipe_token(token))
			return (token);
		if (token->next == NULL)
			return (token);
		token = token->next;
	}
	return (token);
}
