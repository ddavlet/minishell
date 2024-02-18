#include "parsing.h"

t_envvar	*init_envvar(void)
{
	t_envvar	*root;

	root = (t_envvar *)ft_calloc(sizeof(t_envvar), 1);
	if (!root)
	{
		ft_printf("Parsing error: failed to allocate memory \
			for enviromental variables");
		return (NULL);
	}
	root->content = NULL;
	root->exists = false;
	root->child = NULL;
	root->letter = 0;
	return (root);
}
void	add_node(t_envvar *list, char c, const char *content)
{
	t_envvar	*last;
	t_envvar	*new_node;

	last = list;
	while (last->next)
		last = last->next;
	if (content)
	{
		new_node->content = ft_strdup(content);
		new_node->exists = true;
	}
	else
	{
		new_node->content = NULL;
		new_node->exists = false;
	}
	new_node->child = NULL;
	new_node->next = NULL;
	last->next = new_node;
}

int	add_envvar(t_envvar *root, char *envvar, const char *content)
{
	t_envvar	*child;

	child = root;
	while (*envvar)
	{
		while (child && *envvar != child->letter)
			child = child->next;
		if (!child && *(envvar + 1))
			add_node(child, *envvar, NULL);
		else if (!child && !*(envvar + 1))
			add_node(child, *envvar, content);
		else if (*(envvar + 1))
			child = child->child;
		else if (!*(envvar + 1))
			child->content = content;
	}
}
