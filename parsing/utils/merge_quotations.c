/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_quotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vketteni <vketteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:16 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/19 11:35:06 by vketteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

const char	*get_closing_quote(const char *literal, const char *opening)
{
	if (!literal || !opening)
		return (NULL);
	return (ft_strchr(literal, *opening));
}

const char	*get_opening_quote(const char *literal)
{
	char	*single_quote;
	char	*double_quote;

	if (!literal)
		return (NULL);
	single_quote = ft_strchr(literal, '\'');
	while (single_quote && single_quote - literal != 0 && *(single_quote
			- 1) == '\\')
		single_quote = ft_strchr(single_quote + 1, '\'');
	double_quote = ft_strchr(literal, '"');
	while (double_quote && double_quote - literal != 0 && *(double_quote
			- 1) == '\\')
		double_quote = ft_strchr(double_quote + 1, '"');
	if (single_quote && !double_quote)
		return (single_quote);
	if (!single_quote && double_quote)
		return (double_quote);
	if (single_quote < double_quote)
		return (single_quote);
	if (single_quote > double_quote)
		return (double_quote);
	return (NULL);
}

const char	*process_until_quote(const char *joined, const char *quote,
		int *ptr_start_pos, const char *literal)
{
	const char	*tmp;

	tmp = ft_substr(literal, *ptr_start_pos, (quote) - (literal
				+ *ptr_start_pos));
	if (!tmp)
		return (NULL);
	joined = (const char *)ft_strjoin_free((char *)joined, tmp);
	free((char *)tmp);
	*ptr_start_pos += ((quote + 1) - (literal + *ptr_start_pos));
	return (joined);
}

const char	*process_until_end(const char *joined, int start_pos,
		const char *literal)
{
	const char	*tmp;
	int			length;

	length = 0;
	while (*(literal + length))
		length++;
	tmp = ft_substr(literal, start_pos, length);
	if (!tmp)
		return (NULL);
	joined = (const char *)ft_strjoin_free((char *)joined, tmp);
	free((char *)tmp);
	return (joined);
}

const char	*merge_quotations(const char *literal)
{
	const char	*next_quote;
	const char	*joined;
	int			start_pos;

	next_quote = get_opening_quote(literal);
	if (!next_quote)
		return (NULL);
	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	start_pos = 0;
	while (next_quote)
	{
		joined = process_until_quote(joined, next_quote, &start_pos, literal);
		if (!joined)
			return (NULL);
		next_quote = get_closing_quote(literal + start_pos, next_quote);
		joined = process_until_quote(joined, next_quote, &start_pos, literal);
		if (!joined)
			return (NULL);
		next_quote = get_opening_quote(literal + start_pos);
		if (!next_quote)
			joined = process_until_end(joined, start_pos, literal);
	}
	return (joined);
}
