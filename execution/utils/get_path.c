#include "../execution.h"

static char	*get_env_all_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char *envp[])
{
	char	**env_all_path;
	char	*env_path;
	char	*executable_path;
	int		i;

	env_all_path = ft_split(get_env_all_path(envp), ':');
	if (env_all_path == NULL)
		return (NULL);
	i = -1;
	while (env_all_path[++i])
	{
		env_path = ft_strjoin(env_all_path[i], "/");
		executable_path = ft_strjoin(env_path, cmd);
		free(env_path);
		if (access(executable_path, F_OK | X_OK) == 0)
		{
			free_arr2d((void **)env_all_path);
			return (executable_path);
		}
		free(executable_path);
	}
	free_arr2d((void **)env_all_path);
	return (NULL);
}