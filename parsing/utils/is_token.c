#include "../parsing.h"

int	passed_shell_operator(int pos, const char *line)
{
	if (pos == 1 && line[pos - 1] == '|' && line[pos] != '|')
		return (1);
	if (pos == 2 && line[pos - 1] == '|' && line[pos - 2] == '|')
		return (1);
	if (pos == 2 && line[pos - 1] == '&' && line[pos - 2] == '&')
		return (1);
	if (pos > 2 && line[pos] == '&' && line[pos + 1] == '&')
		return (1);
	if (pos > 2 && line[pos] == '|' && line[pos + 1] == '|')
		return (1);
	if (pos > 1 && line[pos] == '|' && line[pos + 1] != '|')
		return (1);
	return (0);
}

int	passed_redir_sign(int pos, const char *line)
{
	if (pos == 1 && line[pos - 1] == '<' && line[pos] != '<')
		return (1);
	if (pos == 2 && line[pos - 1] == '<' && line[pos - 2] == '<')
		return (1);
	if (pos == 1 && line[pos - 1] == '>' && line[pos] != '>')
		return (1);
	if (pos == 2 && line[pos - 1] == '>' && line[pos - 2] == '>')
		return (1);

	if (pos > 2 && line[pos] == '<' && line[pos + 1] == '<')
		return (1);
	if (pos > 1 && line[pos] == '<' && line[pos + 1] != '<')
		return (1);
	if (pos > 2 && line[pos] == '>' && line[pos + 1] == '>')
		return (1);
	if (pos > 1 && line[pos] == '>' && line[pos + 1] != '>')
		return (1);
	return (0);
}

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

int	is_token(int pos, const char *line)
{
	if (!line)
	{
		ft_putendl_fd("line missing", STDERR_FILENO);
		return (0);
	}
	if (line[pos] == 0)
		return (0);
	else if (passed_shell_operator(pos, line))
		return (0);
	else if (passed_redir_sign(pos, line))
		return (0);
	else if (!ft_isspace(line[pos]) && ft_isprint(line[pos]))
		return (1);
	else if (ft_isspace(line[pos]) && is_between_quotes(pos, line))
		return (1);
	else
		return (0);
}
