#include "builtin.h"

int	builtin_exit(char **argv, t_env *root, t_executor *exec)
{
	int	i;

	i = 0;
	(void)root;
	while (argv[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
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
		terminate(exec, ft_atoi(argv[1]) % 256, NULL);
		// return (ft_atoi(argv[1]) % 256);
	}
	terminate(exec, 0, NULL);
	return (0);
}
