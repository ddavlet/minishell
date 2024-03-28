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

void	*error_general(void *ptr, const char *str)
{
	if (ptr)
	{
		if (str)
		{
			ft_putstr_fd(str, 2);
			perror(": undefined error on allocation"); // why perror?
		}
		else
			perror("Undefined error on allocation"); // why perror?
		return (ptr);
	}
	perror("Allocation error:"); // why perror?
	return (NULL);
}

void	*error_near_tocken(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (!token)
		write(2, "newline", 7);
	else if (token[0] == '\\')
		write(2, &(token[1]), ft_strlen(&(token[1])));
	else
		write(2, token,ft_strlen(token));
	ft_putendl_fd("\'", 2);
	return (NULL);
}
