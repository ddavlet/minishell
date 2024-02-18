#include "parsing.h"

void	*error_quot_tockens(char **tokens)
{
	ft_printf("Parsing error: quotation(s) not closed"); // error text;
	terminate_tokens(tokens);
	return (NULL);
}
