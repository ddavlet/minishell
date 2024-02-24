#include "builtin.h"

int builtin_echo(char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	ft_putstr_fd("\n", 1);
	return (0);
}
