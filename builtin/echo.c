#include "builtin.h"

int	builtin_echo(char **argv, t_env *root)
{
	ssize_t	i;
	bool	option;

	(void)root;
	i = 1;
	option = 0;
	while (argv[i])
	{
		while (!option && !ft_strncmp(argv[i], "-n", 3))
			i++;
		option = true;
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (ft_strncmp(argv[1], "-n", 3))
		ft_putstr_fd("\n", 1);
	return (0);
}
