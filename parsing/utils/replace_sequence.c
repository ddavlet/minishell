/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_sequence.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:29:25 by ddavlety          #+#    #+#             */
/*   Updated: 2024/04/18 14:17:16 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	get_replace_count(const char *literal, const char *sequence,
		t_replacer replacer)
{
	const char	*tmp;
	const char	*needle;
	int			count;

	count = 0;
	tmp = literal;
	needle = ft_strnstr(tmp, sequence, ft_strlen(tmp));
	while (needle != NULL)
	{
		count++;
		tmp = needle + replacer.seq_len;
		needle = ft_strnstr(tmp, sequence, ft_strlen(tmp));
	}
	return (count);
}

int	get_result_length(const char *literal, const char *sequence,
		t_replacer replacer)
{
	int	count;

	count = get_replace_count(literal, sequence, replacer);
	return (replacer.literal_len - count * replacer.seq_len + count
		* replacer.rep_len);
}

t_replacer	initialize_replacer(const char *literal, const char *sequence,
		const char *replacement)
{
	t_replacer	replacer;

	replacer.literal_len = strlen(literal);
	replacer.seq_len = strlen(sequence);
	replacer.rep_len = strlen(replacement);
	replacer.result_len = get_result_length(literal, sequence, replacer);
	return (replacer);
}

const char	*replace_loop(const char *literal, const char *sequence,
		const char *replacement, t_replacer replacer)
{
	int			head_len;
	const char	*tmp;
	const char	*current;
	char		*result;
	char		*result_ptr;

	result = (char *)ft_calloc(replacer.result_len + 1, 1);
	if (result == NULL)
		return (NULL);
	result_ptr = result;
	current = literal;
	tmp = ft_strnstr(current, sequence, ft_strlen(current));
	while (tmp != NULL)
	{
		head_len = tmp - current;
		ft_memcpy(result_ptr, current, head_len);
		result_ptr += head_len;
		ft_memcpy(result_ptr, replacement, replacer.rep_len);
		result_ptr += replacer.rep_len;
		current = tmp + replacer.seq_len;
		tmp = ft_strnstr(current, sequence, ft_strlen(current));
	}
	strcpy(result_ptr, current);
	return (result);
}
