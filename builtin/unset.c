#include "builtin.h"

int	builtin_unset(const char **argv, t_env *shell_env)
{
	uint32_t	i;

	i = 1;
	while (argv[i])
		unset_envvar(shell_env, argv[i++]);
	return (0);
}
