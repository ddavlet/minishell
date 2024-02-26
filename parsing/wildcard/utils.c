#include "wildcard.h"

static void	add_envnode(t_tree **list_p, char c, const char *content)
{
	t_tree	*last;
	t_tree	*new_node;

	last = *list_p;
	new_node = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	if (!new_node)
		return ; //dela with this return
	new_node->letter = c;
	if (content)
	{
		new_node->exists = true;
		new_node->name = ft_strdup(content);
	}
	if (!last)
		*list_p = new_node;
	else
	{
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

static void	add_envvar(t_tree *root, const char *envvar, const char *content)
{
	t_tree	**child_p;

	child_p = &root->child;
	while (*envvar)
	{
		while ((*child_p) && *envvar != (*child_p)->letter)
			child_p = &((*child_p)->next);
		if (!(*child_p) && *(envvar + 1))
		{
			add_envnode(child_p, *envvar, NULL);
			child_p = &((*child_p)->child);
		}
		else if (!(*child_p) && !*(envvar + 1))
			add_envnode(child_p, *envvar, content);
		else if (*(envvar + 1))
			child_p = &((*child_p)->child);
		else if (!*(envvar + 1))
		{
			free((*child_p)->name);
			(*child_p)->name = ft_strdup(content);
			(*child_p)->exists = true;
		}
		envvar++;
	}
}

t_tree	*init_tree(const char **envp)
{
	t_tree		*root;
	uint32_t	i;
	// uint32_t	j;

	root = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	if (!root)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		add_envvar(root, envp[i], envp[i]);
		i++;
	}
	return (root);
}
