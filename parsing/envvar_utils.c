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
	return (root);
}

t_envvar	*add_envvar(t_envvar *root, char *envvar)
{

}
