#include "builtin.h"

int	builtin_pwd(char **argv, t_env *root, int out_fd)
{
	char	*pwd;

	(void)argv;
	// if (argv[1])
	// 	return (builtin_err_gen("pwd", "option(s) or argument(s) are not allowed", NULL));
	pwd = find_var(root, ft_strdup("PWD"));
	if (pwd == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory:"
						" getcwd: cannot access parent directories:"
						" No such file or directory\n",
						2);
		return (1);
	}
	ft_putstr_fd(pwd, out_fd);
	ft_putstr_fd("\n", out_fd);
	free(pwd);
	return (0);
}
