/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_contains_quotations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:27:51 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 13:34:50 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	is_first_letter(const char *ptr_char, const char *literal)
{
	if (!literal || !ptr_char)
		return (0);
	if (literal - ptr_char == 0)
		return (1);
	return (0);
}

int	is_escaped(const char *ptr_char, const char *literal)
{
	if (!literal || !ptr_char || (literal - ptr_char) == 0)
		return (0);
	else if (*(ptr_char - 1) == '\\'
		&& !is_escaped(ptr_char - 1, literal))
		return (1);
	return (0);
}

int	contains_quotations(const char *literal)
{
	char	*quotes;

	if (!literal)
		return (0);
	quotes = ft_strchr(literal, '\'');
	if (quotes)
	{
		if (is_first_letter(quotes, literal))
			return (1);
		else if (!is_escaped(quotes, literal) && !is_between_char(quotes
				- literal, literal, '\"'))
			return (1);
	}
	quotes = ft_strchr(literal, '\"');
	if (quotes)
	{
		if (is_first_letter(quotes, literal))
			return (1);
		else if (!is_escaped(quotes, literal) && !is_between_char(quotes
				- literal, literal, '\''))
			return (1);
	}
	return (0);
}

int	argv_contains_quotations(const char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (contains_quotations(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
