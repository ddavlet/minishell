#include "builtin.h"

int	builtin_cd(char **argv, t_env *root)
{
	char	*path;
    int		ret;


	if (argv[2])
		return (builtin_err_gen("cd", "too many arguments", NULL));
	if (!argv[1])
	{
		path = get_envvar("HOME", root);
		if (!path)
			return (builtin_err_gen("cd", "HOME not set", NULL));
	}
	else
		path = argv[1];
    ret = chdir(path);
    if (ret == -1)
    {
        return (builtin_err_gen("cd", "No such file or directory", path));
    }
	append_envp(root, "OLDPWD", find_var(root, "PWD"));
	append_envp(root, "PWD", path);
	return (0);
}
