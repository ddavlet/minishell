#include "builtin.h"

int	builtin_unset(char **argv, t_env *root)
{
	uint32_t	i;

	i = 1;
	while (argv[i])
		unset_envvar(root, argv[i++]);
	return (0);
}
