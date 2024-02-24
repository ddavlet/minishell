#include "builtin.h"

int builtin_cd(char **argv, t_env *root)
{
	char	*path;

	if (argv[1] == NULL)
	{
		path = get_envvar("HOME", root);
		if (path == NULL)
			return (builtin_err_gen("cd", "HOME not set", NULL));
	}
	else
		path = argv[1];
	if (argv[2])
		return (builtin_err_gen("cd", "too many arguments", NULL));
	if (0) // check path?
		return (builtin_err_gen("cd", "No such file or directory", path));
	append_envp(root, "PWD", path);
	return (0);
}
