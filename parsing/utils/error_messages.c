#include "../parsing.h"

int	syntax_error(const char *token_name)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
	write(STDERR_FILENO, token_name, ft_strlen(token_name));
	write(STDERR_FILENO, "'\n", 2);
	return (1);
}
