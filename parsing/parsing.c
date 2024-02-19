#include "parsing.h"

t_oper	parse_rule(char *txt)
{
	txt++; //we don't search for it from the first char + SEGFAULT protection
	while (*txt)
	{
		if (*(txt - 1) != '\\') // add if for quotations
		{
			if (*txt == '|' && *(txt + 1) != '|')
				return (PIPE);
			else if (*txt == '|')
				return (OR);
			else if (*txt == '&' && *(txt + 1) == '&')
				return (AND);
		}
		txt++;
	}
	return (RUN);
}

int	count_commands(char **txt) //here max value of commands is limited to int. Need protection?
{
	int	count;

	count = 1;
	while (*txt)
	{
		if (*txt[0] == '|')
			count++;
		else if (*txt[0] == '&')
			count++;
		txt++;
	}
	return (count);
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

uint32_t	del_pos(const char *txt)
{
	uint32_t	i;

	i = 0;
	while (txt[i])
	{
		if (!ft_isalnum(txt[i]) && txt[i] != '_')
			break ;
		i++;
	}
	return (i);
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
				return (child->content);
			else
				return ("");
		}
		else
			child = child->next;
	}
	return (ft_strdup(""));
}

char	*set_envvar(const char *txt, t_env *root)
{
	char		*new_txt;
	char		*tmp_1;
	char		*tmp_2;
	uint32_t	i;

	i = 0;
	while (txt[i] && txt[i] != '*')
		i++;
	if (!ft_isalnum(txt[i + 1]) && txt[i + 1] != '_')
		return (ft_strdup(txt));
	new_txt = ft_substr(txt, 0, i);
	if (!new_txt)
		return (NULL); // ?? protect
	tmp_1 = ft_substr(txt, i + 1, del_pos(&txt[i + 1]));
	if (!tmp_1)
		return (NULL); // ?? protect
	tmp_2 = find_var(root, tmp_1);
	if (!tmp_2)
		return (NULL); // ?? protect
	free(tmp_1);
	tmp_1 = new_txt;
	new_txt = ft_strjoin(tmp_1, tmp_2); // protect
	free(tmp_1);
	free(tmp_2);
	tmp_1 = new_txt;
	new_txt = ft_strjoin(tmp_1, &txt[i + del_pos(&txt[i + 1]) + 1]);
	free(tmp_1);
	return (new_txt);
}

void	get_variable(char **tokens, t_env *root)
{
	ssize_t	i;
	char	*tmp;

	i = 0;
	while (tokens[i])
	{
		if (!(tokens[i][0] == '\''))
		{
			while (ft_strchr(tokens[i], '*'))
			{
				tmp = tokens[i];
				tokens[i] = set_envvar(tmp, root);
				free(tmp);
			}
		}
		i++;
	}

}

t_cmd	**parse_text(char *txt, t_env *root)
{
	t_cmd	**commands;
	// int		i;
	char	**tokens;
	// int		count; //assume that number of command are less then int

	tokens = pars_split(txt);

	tokens = merge_quotations(tokens);
	if (!tokens)
		return (NULL); // ?? catch it, mein Freund
	get_variable(tokens, root);
	debug_print_tokens(tokens);
	(void)commands;
	return (NULL);
}

// test purmose main:

