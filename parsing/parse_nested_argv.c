/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nested_argv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:30:43 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:30:43 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse_nested_argv(char ***ptr_argv, t_token *start, t_token *end)
{
	char **new;

	if (!ptr_argv || !start || !end)
		return (-1);
	new = (char **)ft_calloc(4, sizeof(char *));
	new[0] = ft_strdup("minishell");
	if (!new[0])
	{
		free_argv((const char **)new);
		return (-1);
	}
	new[1] = ft_strdup("-n");
	if (!new[1])
	{
		free_argv((const char **)new);
		return (-1);
	}
	new[2] = ft_substr(start->literal, 1, ft_strlen(start->literal) - 2);
	if (!new[2])
	{
		free_argv((const char **)new);
		return (-1);
	}
	*ptr_argv = new;
	return (0);
}
