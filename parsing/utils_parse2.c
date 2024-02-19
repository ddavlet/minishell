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
	terminate_tokens(tokens);
	return (merged);
}

char	*find_var(t_env	*root, char *search)
{
	t_env	*child;

	child = root->child;
	if (!search)
		return (NULL);
	while (child)
	{
		if (child->letter == *search && *(search + 1)) // need to be checked~
		{
			child = child->child;
			search++;
		}
		else if (child->letter == *search && !*(search + 1))
		{
			if (child->exists == true)
				return (ft_strdup(child->content));
			else
				return (ft_strdup(""));
		}
		else
			child = child->next;
	}
	return (ft_strdup(""));
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
