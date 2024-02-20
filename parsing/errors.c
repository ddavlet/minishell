#include "parsing.h"

void	*error_quot_tockens(char **tokens)
{
	ft_putendl_fd("Parsing error: quotation(s) not closed", 2);
	terminate_ptr_str(tokens);
	return (NULL);
}

void	*error_parsing_redir(t_redir *redir_l)
{
	ft_putendl_fd("Parsing error: fail to read redirection key", 2);
	terminate_redirs(redir_l); // ??
	return (NULL);
}

void	*error_env_init(void)
{
	ft_putendl_fd("Parsing error: failed to allocate memory \
		for enviromental variables", 2);
	return (NULL);
}

void	*error_general(void *ptr)
{
	if (ptr)
	{
		perror("Undefined error on allocation");
		return (ptr);
	}
	perror("Allocation error:");
	return (NULL);
}

void	*error_near_tocken(char *token)
{
	printf("minishell: syntax error near unexpected token `%s'", token);
	return (NULL);
}
