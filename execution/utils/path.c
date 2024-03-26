#include "../execution.h"

char	*build_path_from_env(char *name)
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