#include "builtin.h"

int	builtin_env(const char **argv, t_env *root)
{
	uint32_t	i;

	i = 0;
	if (argv[1])
		return (builtin_err_gen("env", \
		"option(s) or argument(s) are not allowed", NULL));
	while (root->envp[i])
		ft_putendl_fd(root->envp[i++], STDOUT_FILENO);
	return (0);
}
