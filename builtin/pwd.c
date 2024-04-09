#include "builtin.h"

int	builtin_pwd(const char **argv, t_env *shell_env)
{
	char	*pwd;

	(void)argv;
	// if (argv[1])
	// 	return (builtin_err_gen("pwd", "option(s) or argument(s) are not allowed", NULL));
	pwd = get_shell_variable(shell_env, "PWD");
	if (pwd == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory:"
						" getcwd: cannot access parent directories:"
						" No such file or directory\n",
						2);
		return (1);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
	return (0);
}
