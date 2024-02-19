#include "parsing.h"

t_redir	*add_redirnode(const char *key, const char *value)
{
	t_redir	*new_node;

	new_node = (t_redir *)ft_calloc(sizeof(t_redir), 1);
	if (!new_node)
		return (NULL); // catch it!
	if (key[0] == '<')
	{
		if (key[1] == '<')
			new_node->redir_sym = HEAR_DOC;
		else
			new_node->redir_sym = RED_INP;
	}
	else if (key[0] == '>')
	{
		if (key[1] == '<')
			new_node->redir_sym = RED_OUT;
		else
			new_node->redir_sym = APP_OUT;
	}
	else
	{
		free(new_node);
		return (NULL); // catch
	}
	new_node->redir_name = ft_strdup(value);
	return (new_node);
}

void	terminate_redirs(t_redir *redir_l)
{
	t_redir	*tmp;

	if (!redir_l)
		return ;
	while (redir_l)
	{
		tmp = redir_l;
		redir_l = redir_l->next;
		free(tmp->redir_name);
		free(tmp);
	}
}
