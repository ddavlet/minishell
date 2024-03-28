#include "parsing2.h"

int	is_between_char(int pos, const char *line, char c)
{
	const char	*start;
	const char	*end;

	start = ft_strchr(line, c);
	while (start && *(start + 1))
	{
		end = ft_strchr(start + 1, c);
		if (end && line + pos > start && line + pos < end)
			return (1);
		else if (!end || !(*(end + 1)))
			return (0);
		start = ft_strchr(end + 1, c);
	}
	return (0);
}

int	is_between_quotes(int pos, const char *line)
{
	if (is_between_char(pos, line, '\'') || is_between_char(pos, line, '\"'))
		return (1);
	return (0);
}

int is_between_redir(int pos, const char *line)
{
    if (!(line[0] == '<' || line[0] == '>'))
        return (0);
    if (ft_strncmp(line, "<<", 2) || ft_strncmp(line, ">>", 2))
        line += 2;
    else
        line++;
    while (ft_isspace(line))
        line++;
    if ()
}

int	is_token(const char *line, const char *token_end)
{
	if (!line || !token_end)
		return (0);
	if (ft_isspace(*token_end) && is_between_quotes(line, token_end - line))
		return (1);
	else if (ft_isspace(*token_end) && is_between_redir(line, token_end - line))
		return (1);
    else
        return (0);
}

void	free_tokens(t_token *tokens)
{
	t_token *tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->literal);
		free(tokens);
		tokens = tmp;
	}
}