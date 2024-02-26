#include "parsing.h"

static int	remove_envvar(t_env	*root, const char *search)
{
	t_env	*child;

	child = root->child;
	if (!search)
		return (1);
	while (child)
	{
		if (child->letter == *search && *(search + 1))
		{
			child = child->child;
			search++;
		}
		else if (child->letter == *search && !*(search + 1))
		{
			if (child->exists == true)
			{
				free(child->content);
				child->exists = false;
				return (0);
			}
		}
		else
			child = child->next;
	}
	return (1);
}

int	unset_envvar(t_env *root, const char *to_find)
{
	uint32_t	i;

	i = 0;
    (void)i;
	if (remove_envvar(root, to_find))
		return (1);
	else
	{
		terminate_ptr_str(root->envp);
		root->envp = init_envv(root);
	}
	return (0);
}
