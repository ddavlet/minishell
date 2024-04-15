#include "parsing.h"

t_token	*initialize_token(const char *literal)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->literal = literal;
	token->next = NULL;
	return (token);
}

const char	*get_parenthesis(const char *line)
{
	const char	*end;
	const char	*string_literal;

	end = line;
	while (*end && *end != ')')
		end++;
	if (*end == 0)
		return (NULL);
	string_literal = (const char *)ft_substr(line, 0, (end + 1) - line);
	return (string_literal);
}

t_token	*get_token(const char *line)
{
	const char	*string_literal;
	const char	*end;

	end = line;
	if (*line == '(')
		string_literal = get_parenthesis(line);
	else
	{
		while (is_token(end - line, line))
			end++;
		string_literal = (const char *)ft_substr(line, 0, end - line);
	}
	if (!string_literal)
		return (NULL);
	return (initialize_token(string_literal));
}

void	add_token(t_token **tokens, t_token *new)
{
	t_token	*last;

	last = *tokens;
	if (last == NULL)
		*tokens = new;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

t_token	*tokenizer(const char *line)
{
	t_token	*tokens;
	t_token	*new;

	// if (!line)
	// 	return (NULL);
	if (!line || !*line)
		return (get_token(line));
	tokens = NULL;
	while (*line)
	{
		if (ft_isspace(*line))
			line++;
		else
		{
			new = get_token(line);
			if (new == NULL)
			{
				free_tokens(tokens);
				break ;
			}
			add_token(&tokens, new);
			line += ft_strlen(new->literal);
		}
	}
	if (tokens == NULL)
		return (get_token(line));
	return (tokens);
}
