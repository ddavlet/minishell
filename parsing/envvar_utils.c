#include "parsing.h"

t_env	*init_env(void)
{
	t_env	*root;

	root = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!root)
	{
		ft_printf("Parsing error: failed to allocate memory \
			for enviromental variables");
		return (NULL);
	}
	return (root);
}

void	add_node(t_env **list_p, char c, const char *content)
{
	t_env	*last;
	t_env	*new_node;

	last = *list_p;
	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		return ; //dela with this return
	if (content)
	{
		new_node->content = ft_strdup(content);
		new_node->exists = true;
	}
	new_node->letter = c;
	if (!last)
		*list_p = new_node;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

void	add_envvar(t_env *root, char *envvar, const char *content)
{
	t_env	**child_p;

	child_p = &root->child;
	while (*envvar)
	{
		while ((*child_p) && *envvar != (*child_p)->letter)
			child_p = &((*child_p)->next);
		if (!(*child_p) && *(envvar + 1))
		{
			add_node(child_p, *envvar, NULL);
			child_p = &((*child_p)->child);
		}
		else if (!(*child_p) && !*(envvar + 1))
			add_node(child_p, *envvar, content);
		else if (*(envvar + 1))
			child_p = &((*child_p)->child);
		else if (!*(envvar + 1))
			(*child_p)->content = ft_strdup(content);
		envvar++;
	}
}

void	terminate_env(t_env *root)
{
	t_env	*tmp;

	if (!root)
		return ;
	while (root)
	{
		terminate_env(root->child);
		tmp = root;
		root = root->next;
		free(tmp->content);
		free(tmp);
	}
}
