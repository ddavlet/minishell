/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddavlety <ddavlety@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 19:59:03 by ddavlety          #+#    #+#             */
/*   Updated: 2024/02/15 20:55:35 by ddavlety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static unsigned int	ft_count_len(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != c && s[i] && !ft_isexeption(s[i]))
		i++;
	return (i);
}

static unsigned int	ft_counter(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			s += (ft_count_len(s, c) - 1);
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

char	**pars_split(char const *s, char c)
{
	char	**split;
	int		word;

	if (!s)
		return (0);
	word = 0;
	split = (char **)malloc((ft_counter(s, c) + 1) * sizeof(char *));
	if (!split)
		return (0);
	split[ft_counter(s, c)] = 0;
	while (*s)
	{
		if (ft_isexeption(*s))
			break ;
		if (*s != c)
		{
			split[word] = ft_substr(s, 0, ft_count_len(s, c));
			if (!split[word])
				ft_free_all(split, word);
			word++;
			s += (ft_count_len(s, c) - 1);
		}
		s++;
	}
	return (split);
}
