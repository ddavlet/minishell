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
		if (!ft_isalnum(txt[i]))
			break ;
		i++;
	}
	return (i);
}

char	*find_var(t_env	*root, char *search)
{
	t_env	*child;

	child = root->child;
	while (child)
	{
		if (child->letter == *search && *(search + 1))
		{
			child = child->child;
			search++;
		}
		else if (child->letter == *search && !*(search + 1))
		{
			free(search);
			if (child->exists == true)
				return (child->content);
			else
				return ("");
		}
		else
			child = child->next;
	}
	free(search);
	return ("");
}

char	*set_envvar(const char *txt, t_env *root)
{
	char		*new_txt;
	char		*tmp;
	uint32_t	i;

	i = 0;
	while (txt[i] && txt[i] == '$' && !del_pos(&txt[i + 1]))
		i++;
	if (!txt[i])
		return (ft_strdup(txt)); // ?? protect
	new_txt = ft_substr(txt, 0, i); //protect
	tmp = new_txt;
	new_txt = ft_strjoin(tmp, find_var(root, ft_substr(txt, i, del_pos(&txt[i])))); // protect
	free(tmp);
	i += del_pos(&txt[i]);
	tmp = new_txt;
	new_txt = ft_strjoin(tmp, set_envvar(&txt[i], root));
	// recursion to find all $ARGS ??
	return (new_txt);
}

void	get_variable(char **tokens, t_env *root)
{
	ssize_t	i;
	char	*tmp;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '\"')
		{
			tmp = tokens[i];
			tokens[i] = set_envvar(tmp, root);
			free(tmp);
		}
		i++;
	}

}

t_com	**parse_text(char *txt, t_env *root)
{
	t_com	**commands;
	// int		i;
	char	**tokens;
	// int		count; //assume that number of command are less then int

	tokens = pars_split(txt);
	// check tokens (i.e. "&" or "|||"), since it is limitation of split funtion
	tokens = merge_quotations(tokens);
	debug_print_tokens(tokens);
	if (!tokens)
		return (NULL); // ?? catch it, mein Freund
	get_variable(tokens, root);
	debug_print_tokens(tokens);
	(void)commands;
	return (NULL);
}

// test purmose main:

