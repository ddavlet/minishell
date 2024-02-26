#include "builtin.h"

int	builtin_echo(char **argv, t_env *root)
{
	ssize_t	i;

	(void)root;
	i = 0;
	while (argv[i] && !ft_strncmp(argv[i], "-n", 3))
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (ft_strncmp(argv[1], "-n", 3))
		ft_putstr_fd("\n", 1);
	return (0);
}
