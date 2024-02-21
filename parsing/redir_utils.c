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

t_redir	*init_redir(char **tokens, ssize_t prev, ssize_t next)
{
	t_redir		*redir;
	ssize_t		i;

	if (prev == 1)
		prev--;
	i = prev;
	redir = NULL;
	while (i < next)
	{
		if (ft_isrediraction(tokens[i]))
		{
			append_redirnode(&redir, ft_isrediraction(tokens[i]), tokens[i + 1]);
			i++;
		}
		i++;
	}
	return (redir);
}
