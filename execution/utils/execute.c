#include "../execution.h"

static char	*build_path_from_env(char *name)
{
    char    **env_paths;
	char	*path;
	char	*executable_path;
	int		i;

    env_paths = ft_split(getenv("PATH"), ':');
	if (!env_paths)
        return (NULL);
	i = -1;
	while (env_paths[++i])
	{
		path = ft_strjoin(env_paths[i], "/");
		executable_path = ft_strjoin_free(path, name);
		if (access(executable_path, F_OK | X_OK) == 0)
		{
			free_arr2d((void **)env_paths);
			return (executable_path);
		}
		free(executable_path);
	}
	free_arr2d((void **)env_paths);
	return (NULL);
}

int	execute(t_executor *exec, char **argv, char **envp)
{
	char	*path;

	if (!argv || !envp)
	{
		terminate(exec, EXIT_FAILURE, "execute: parameter check failed");\
	}
	if (ft_strchr(argv[0], '/') == NULL)
	{
		path = build_path_from_env(argv[0]);
		if (path == NULL)
			terminate(exec, EXIT_FAILURE, "minishell: couldn't find path");
	}
	else
		path = argv[0];
	if (execve(path, argv, envp) == -1)
		terminate(exec, EXIT_FAILURE, "minishell: execution failure");
	return (0);
}
