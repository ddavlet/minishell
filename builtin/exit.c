#include "builtin.h"

int builtin_exit(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	if (i == 2)
	{
		if (ft_isnumber(args[1]) == 0)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
		return (ft_atoi(args[1]) % 256);
	}
	return (0);
}
