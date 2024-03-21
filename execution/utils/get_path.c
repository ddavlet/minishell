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
    if (ft_strchr(cmd, '/') == NULL)
        return (get_path_from_env(cmd, envp));
    else if (cmd[0] == '/')
        return (cmd);
    else
        return (get_path_from_relative(cmd));
}

char	*get_path_from_env(char *cmd, char *envp[])
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

char    *get_path_from_relative(char *path, char *name)
{
    char    *path_abs;
    char    *relative_part;

    path_abs = NULL;
    if (ft_strncmp(path, "../", 3) == 0)
        path_abs = build_relativ_from_parent(path);
    else if (ft_strncmp(path, "./", 2) == 0)
        path_abs = build_relativ_from_working(path);
    else if (ft_strncmp(path, "~/", 2) == 0)
        path_abs = build_relativ_from_tilde(path);
    else
        return (NULL);
}