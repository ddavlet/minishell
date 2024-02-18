/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:59:03 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/17 21:19:36 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	ft_chekc_token(char c)
{
	if (!c)
		return (1);
	if (ft_isspace(c))
		return (1);
	if (ft_isexeption(c))
		return (2);
	if (ft_isquotation(c))
		return (3);
	return (0);
}

static unsigned int	ft_count_len(char const **str)
{
	unsigned int	i;
	const char		*s;

	i = 0;
	s = *str;
	if (ft_chekc_token(s[i]) == 2)
	{
		while (ft_chekc_token(s[i]) == 2)
			i++;
		return (i);
	}
	if (ft_chekc_token(s[i]) == 3)
	{
		return (1);
	}
	while (s[i] && !ft_chekc_token(s[i]))
		i++;
	return (i);
}

static ssize_t	ft_counter(char const *s) // chekc this function..
{
	ssize_t	i;

	i = 0;
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			i++;
			s += (ft_count_len(&s) - 1);
		}
		s++;
	}
	return (i);
}

static void	ft_free_all(char **ptr, int n)
{
	while (n > -1)
	{
		free(*ptr++);
		n--;
	}
	free (ptr);
}

char	**pars_split(char const *s)
{
	char		**split;
	ssize_t		word;

	if (!s)
		return (0);
	word = 0;
	split = (char **)ft_calloc((ft_counter(s) * 2), sizeof(char *));
	if (!split)
		return (0);
	while (*s)
	{
		if (!ft_isspace(*s))
		{
			split[word] = ft_substr(s, 0, ft_count_len(&s));
			if (!split[word])
				ft_free_all(split, word);
			s += (ft_count_len(&s) - 1);
			word++;
		}
		else
			split[word++] = ft_strdup(" ");
		s++;
	}
	free(split[word]);
	split[word] = NULL;
	return (split);
}
