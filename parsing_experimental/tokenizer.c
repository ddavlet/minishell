#include "parsing2.h"

t_token	*initialize_token(const char *literal)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->literal = literal;
	token->next = NULL;
	token->type = WHITE_SPACE;
	return (token);
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

t_token_type	get_next_type(const char *line)
{
	if (!line)
		return (OTHER);
	else if (ft_isspace(*line))
		return (WHITE_SPACE);
	else if (is_redir_token(line)) // *line == '<' || *line == '>'
		return (REDIRECTION);
	else if (is_logic_token(line))
		return (LOGIC_OPERATOR);
	else if (is_parenthesis_token(line))
		return (PARENTHESIS);
	else if (is_pipe_token(line))
		return (PIPE);
	else if (is_quotation_token(line))
		return (QUOTATION);
	else if (is_variable_token(line))
		return (VARIABLE);
	else
		return (OTHER);
}

t_token	*next_token(const char *line, t_token_type type)
{
	if (type == WHITE_SPACE)
		return (white_space_token(line));
	else if (type == COMMAND)
		return (command_token(line));
	else if (type == LOGIC_OPERATOR)
		return (logic_token(line));
	else if (type == PARENTHESIS)
		return (parenthesis_token(line));
	else if (type == PIPE)
		return (pipe_token(line));
	else if (type == QUOTATION)
		return (quotation_token(line));
	else if (type == REDIRECTION)
		return (redirection_token(line));
	else if (type == VARIABLE)
		return (variable_token(line));
	else if (type == OTHER)
		return (NULL);
}

t_token	*tokenizer(const char *line)
{
	t_token			*tokens;
	t_token			*new;
	t_token_type	type;

	tokens = NULL;
	while (*line)
	{
		type = get_next_type(line);
		new = next_token(line, type);
		add_token(&tokens, new);
		line += ft_strlen(new->literal);
	}
	return (tokens);
}