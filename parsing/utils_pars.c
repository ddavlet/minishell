/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 20:00:39 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/16 16:07:26 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isexeption(char c)
{
	if (c == '|') // add more exeptions if needed
		return (1);
	if (c == '&')
		return (1);
	return (0);
}

int	ft_isquotation(char c)
{
	if (c == '\'')
		return (1);
	if (c == '\"')
		return (1);
	return (0);
}
