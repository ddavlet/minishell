#include "parsing2.h"

t_token	*initialize_token(const char *literal)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->literal = literal;
	token->next = NULL;
	return (token);
}

t_token	*get_token(const char *line)
{
	const char	*string_literal;
	const char	*token_end;

	token_end = line;
	while (is_token(line, token_end))
		token_end++;
	string_literal = (const char *)ft_substr(line, 0, token_end - line);
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

	tokens = NULL;
	while (*line)
	{
		if (ft_isspace(*line))
			line++;
		else
		{
			new = get_token(line);
			add_token(&tokens, new);
			line += ft_strlen(new->literal);
		}
	}
	return (tokens);
}
