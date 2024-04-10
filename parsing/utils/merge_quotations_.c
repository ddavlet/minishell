#include "../parsing.h"

const char	*get_closing_quote(const char *literal, const char *opening)
{
	if (!literal || !opening)
		return (NULL);
	return (ft_strchr(literal, *opening));
}

const char	*get_opening_quote(const char *literal)
{
	char	*single_quote;
	char	*double_quote;

	if (!literal)
		return (NULL);
	single_quote = ft_strchr(literal, '\'');
	double_quote = ft_strchr(literal, '\"');
	if (single_quote && !double_quote)
		return (single_quote);
	if (!single_quote && double_quote)
		return (double_quote);
	if (single_quote < double_quote)
		return (single_quote);
	if (single_quote > double_quote)
		return (double_quote);
	return (NULL);
}

/*
 *	concatenate string from src[start] with length to dst
 */
void	merge_(char **dst_ptr, const char *src, const char *start, int length)
{
	char	*substring;

	if (!*dst_ptr)
	{
		ft_putendl_fd("failed to merge_ argument", STDERR_FILENO);
		return ;
	}
	substring = ft_substr(src, start - src, length);
	if (!substring)
	{
		free(*dst_ptr);
		ft_putendl_fd("failed to merge_ argument", STDERR_FILENO);
		return ;
	}
	*dst_ptr = ft_strjoin_free(*dst_ptr, substring);
	free(substring);
}

void	merge_quotations_loop(char **result_ptr, const char *literal)
{
	const char	*end;
	const char	*quote;
	const char	*start;

	quote = get_opening_quote(literal);
	if (!quote)
	{
		free(*result_ptr);
		return ;
	}
	start = literal;
	while (quote)
	{
		merge_(result_ptr, literal, start, (quote) - start);
		start = quote + 1;
		quote = get_closing_quote(start, quote);
		merge_(result_ptr, literal, start, (quote) - start);
		start = quote + 1;
		quote = get_opening_quote(start);
	}
	end = literal + ft_strlen(literal);
	merge_(result_ptr, literal, start, (end) - start);
}

char	*merge_quotations_(const char *literal)
{
	char	*string_result;
	char	*tmp;

	string_result = ft_strdup("");
	if (!string_result)
		return (NULL);
	merge_quotations_loop(&string_result, literal);
    tmp = string_result;
    string_result = escape_quotes(string_result);
	free(tmp);
    return (string_result);
}
