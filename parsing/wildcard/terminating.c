#include "wildcard.h"

void	terminate_tree(t_tree *tree)
{
	t_tree	*tmp;

	if (!tree)
		return ;
	while (tree)
	{
		terminate_tree(tree->child);
		tmp = tree->next;
		free(tree->name);
		free(tree);
		tree = tmp;
	}
}
