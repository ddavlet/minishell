#include "parsing.h"

static t_redir	*ft_redirlast(t_redir *node)
{
	t_redir	*tmp;

	if (!node)
		return (NULL);
	tmp = node;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static t_redir	*new_redirnode(t_red_sym key, const char *value)
{
	t_redir	*new_node;

	new_node = (t_redir *)ft_calloc(sizeof(t_redir), 1);
	if (!new_node)
		return (error_general(new_node, "redirection structure")); // catch it!
	new_node->redir_sym = key;
	new_node->redir_name = ft_strdup(value);
	return (new_node);
}

void	append_redirnode(t_redir **redir, t_red_sym	key, const char *value)
{
	t_redir	*node_last;

	node_last = ft_redirlast(*redir);
	if (!value)
		return ; // edge case redirection, throw error
	if (!node_last)
		*redir = new_redirnode(key, value);
	else
		node_last->next = new_redirnode(key, value);
}

t_redir	**init_redir(char **tokens, int len)
{
	t_redir	**redir;
	// int		i;

	redir = (t_redir **)ft_calloc(sizeof(t_redir *), 1);
	if (!redir)
		return (error_general(redir, "redirection structure"));
	// while (i < len)
	// {
	// 	if (tokens[i][0] == '')
	// 		return ;
	// }
	(void)tokens;
	(void)len;
	return (NULL);
}
