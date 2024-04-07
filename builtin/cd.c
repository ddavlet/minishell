#include "builtin.h"

static char	*build_path(char *dir)
{
	char	*cwd;
	char	*path;
	char	*cwd_with_slash;

	(void)dir;
	cwd = getcwd(NULL, 0);
	cwd_with_slash = ft_strjoin(cwd, "/");
	free(cwd);
	if (!cwd_with_slash)
		return (NULL);
	path = ft_strjoin(cwd_with_slash, dir);
	free(cwd_with_slash);
	if (!path)
		return (NULL);
	return (path);
}

int	builtin_cd(char **argv, t_env *root)
{
	char			*path;
	char			*cwd;

	if (argv[1] && argv[2])
		return (builtin_err_gen("cd", "too many arguments", NULL));
	if (!argv[1])
	{
		path = get_shell_variable(root, "HOME");
		if (!path)
			return (builtin_err_gen("cd", "HOME not set", NULL));
	}
	else if (*argv[1] == '/')
		path = argv[1];
	else if (*argv[1] == '~')
	{
		path = ft_strjoin_free(get_shell_variable(root, "HOME"), &argv[1][1]);
	}
	else
		path = build_path(argv[1]);
	chdir(path);
	cwd = getcwd(NULL, 0);
	append_envp(root, "OLDPWD", get_shell_variable(root, "PWD"));
	append_envp(root, "PWD", cwd);
	free(cwd);
	return (0);
}
