#include "parsing.h"

char	*merge_to_char(char **tokens, ssize_t b_q, ssize_t e_q)
{
	char	*merged;
	char	*tmp;

	merged = ft_strdup(tokens[b_q++]);
	while (b_q <= e_q)
	{
		tmp = merged;
		merged = ft_strjoin(tmp, tokens[b_q]);
		free(tmp);
		(b_q)++;
	}
	return (merged);
}

char	**merge_funct(char **tokens, ssize_t b_q, ssize_t e_q)
{
	char	**merged;
	ssize_t	i;
	ssize_t	j;
	ssize_t	len;

	i = 0;
	while (tokens[i])
		i++;
	j = 0;
	len = i - (e_q - b_q);
	merged = (char **)ft_calloc(sizeof(char *), len + 1);
	while (j < len)
	{
		if (j < b_q)
			merged[j] = ft_strdup(tokens[j]);
		else if (b_q == j)
			merged[j] = merge_to_char(tokens, b_q, e_q);
		else
			merged[j] = ft_strdup(tokens[++e_q]);
		j++;
	}
	terminate_ptr_str(tokens);
	return (merged);
}

int	contain_quotations(char **tokens)
{
	ssize_t	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_isquotation(tokens[i][0]) && !tokens[i][1])
			return (1);
		i++;
	}
	return (0);
}

char	**merge_quotations(char **tokens)
{
	ssize_t	i;
	ssize_t	b_q;
	t_quote	type_q;

	b_q = 0;
	i = 0;
	while (tokens[i])
	{
		type_q = ft_isquotation(tokens[i][0]);
		if (type_q)
		{
			b_q = i++;
			while (ft_isquotation(tokens[i][0]) != type_q && tokens[i])
				i++;
			if (!tokens[i])
				return (error_quot_tockens(tokens));
			type_q = ZERO_Q;
			tokens = merge_funct(tokens, b_q, i);
			i = b_q;
		}
		i++;
	}
	return (tokens);
}

char	**parse_delspace(char **tokens)
{
	ssize_t	i;
	ssize_t	j;
	char	**new_arr;

	i = 0;
	j = 0;
	new_arr = (char **)ft_calloc(sizeof(char *), (arrlen_nosspace(tokens) + 1));
	while (tokens[i])
	{
		if (tokens[i][0] == 0)
			i++;
		else
			new_arr[j++] = ft_strdup(tokens[i++]);
	}
	terminate_ptr_str(tokens);
	return (new_arr);
}
