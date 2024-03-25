#include "builtin.h"

int	builtin_exit(char **argv, t_env *root)
{
	int	i;

	i = 0;
	(void)root;
	while (argv[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (i == 2)
	{
		if (!ft_isnumber(argv[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
		exit(ft_atoi(argv[1]) % 256);
		// return (ft_atoi(argv[1]) % 256);
	}
	exit (EXIT_SUCCESS);
}
