#include "builtin.h"

int	builtin_exit(const char **argv, t_env *shell_env)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	if (i > 2)
	{
        terminate_env(shell_env);
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (i == 2)
	{
		if (!ft_isnumber((char *)argv[1]))
		{

			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(argv[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
            terminate_env(shell_env);
			return (255);
		}
        terminate_env(shell_env);
		exit(ft_atoi(argv[1]) % 256);
		// return (ft_atoi(argv[1]) % 256);
	}
    terminate_env(shell_env);
	exit (EXIT_SUCCESS);
}
