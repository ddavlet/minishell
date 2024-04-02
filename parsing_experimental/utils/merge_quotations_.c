#include "../parsing2.h"

const char	*merge_quotations_(const char *literal)
{
    char	*arg;
    char	*next_quote; 
    char	*start; 

    next_quote = get_quote(literal);
    if (!next_quote)
        return (NULL);
    start = literal;
	while (next_quote)
	{
        arg = merge(arg, literal, start, next_quote - start);
        if (!arg)
            return (NULL);
        start +=  next_quote - start;
        if (get_quote(next_quote + 1))
        {
            arg = merge(arg, literal, next_quote, get_quote(next_quote + 1))
        }
	}
		// if (!ft_strchr(literal + end, '\''))
		// 	join_until(arg, '\'', literal + start)
		// if (literal[end] == '\'')
		// {
		// 	new = ft_substr(literal, start, end - start);
		// 	if (!new)
		// 		return (NULL);
		// 	arg = ft_strjoin_free(arg, new);
		// 	free(new);
		// 	if (!arg)
		// 		return (NULL);
		// }
	// 	end = ft_strchr(literal + end + 1, '\'') - (literal + start);
	// else if (literal[end] == '\"')
	// 	end = ft_strchr(literal + end + 1, '\"') - (literal + start);
	// end++;
}