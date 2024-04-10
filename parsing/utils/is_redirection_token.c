#include "../parsing.h"

int	is_redirection_token(t_token *token)
{
	if (!token)
	{
		ft_putendl_fd("token missing", STDERR_FILENO);
		return (0);
	}
	if (ft_strncmp(token->literal, "<", ft_strlen("<")) == 0
		|| ft_strncmp(token->literal, ">", ft_strlen(">")) == 0
		|| ft_strncmp(token->literal, "<<", ft_strlen("<<")) == 0
		|| ft_strncmp(token->literal, ">>", ft_strlen(">>")) == 0)
		return (1);
	return (0);
}