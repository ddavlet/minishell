#include "parsing.h"

t_redir	*initialize_redirection(const char *symbol, const char *name)
{
	t_redir	*redir;

	if (!symbol || !name)
	{
		ft_putendl_fd("failed to initialize redirection", STDERR_FILENO);
		return (NULL);
	}
	redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (!redir)
	{
		ft_putendl_fd("failed to initialize redirection", STDERR_FILENO);
		return (NULL);
	}
	if (ft_strncmp(symbol, "<", ft_strlen(symbol) + 1) == 0)
		redir->redir_sym = RED_INP;
	else if (ft_strncmp(symbol, "<<", ft_strlen(symbol) + 1) == 0)
		redir->redir_sym = HEAR_DOC;
	else if (ft_strncmp(symbol, ">", ft_strlen(symbol) + 1) == 0)
		redir->redir_sym = RED_OUT;
	else if (ft_strncmp(symbol, ">>", ft_strlen(symbol) + 1) == 0)
		redir->redir_sym = APP_OUT;
	redir->redir_name = ft_strdup((const char *)name);
	return (redir);
}

t_redir	*get_redirection(t_token *token)
{
	t_redir		*redir;
	const char	*name;
	const char	*symbol;

	name = token->literal;
	while (*name == '<' || *name == '>')
		name++;
	symbol = (const char *)ft_substr(token->literal, 0, name - token->literal);
	if (*name == '\0')
		name = (const char *)ft_strdup(token->next->literal);
	else
		name = (const char *)ft_strdup(name);
	redir = initialize_redirection(symbol, name);
	free((char *)symbol);
	free((char *)name);
	return (redir);
}

void	add_redirection(t_redir **ptr_redirs, t_redir *new)
{
	if (!ptr_redirs || !new)
	{
		ft_putendl_fd("failed to add redirection", STDERR_FILENO);
		return ;
	}
	if (*ptr_redirs != NULL)
	{
		while ((*ptr_redirs)->next)
			ptr_redirs = &((*ptr_redirs)->next);
		(*ptr_redirs)->next = new;
	}
	else
		*ptr_redirs = new;
}

int parse_redirections(t_redir **ptr_redirs, t_token *start, t_token *end)
{
	t_redir	*new;
	t_token	*token;

	token = start;
	while (token != end->next)
	{
		if (is_redirection_token(token))
		{
			new = get_redirection(token);
			if (!new)
			{
				free_redirections(*ptr_redirs);
				return (-1);
			}
			add_redirection(ptr_redirs, new);
		}
		token = token->next;
	}
	return (0);
}
