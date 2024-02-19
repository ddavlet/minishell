#include "parsing.h"

void	*error_quot_tockens(char **tokens)
{
	ft_putendl_fd("Parsing error: quotation(s) not closed", 2);
	terminate_tokens(tokens);
	return (NULL);
}

void	*error_parsing_redir(t_redir *redir_l)
{
	ft_putendl_fd("Parsing error: fail to read redirection key", 2);
	terminate_redirs(redir_l); // ??
	return (NULL);
}
