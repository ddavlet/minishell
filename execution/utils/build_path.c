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
		path = ft_strjoin_free(env_paths[i], "/");
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

char	*build_relativ_from_parent(char *relative_path)
{
	char	*cwd;
	char	*path;
	char	*tmp;
	char	*parent_dir;

	if (!relative_path)
		return (NULL);
	path = ft_strdup(relative_path + 2);
	if (!path)
		return (NULL);
	parent_dir = get_parent_dir(getcwd(NULL, 0));
	if (!parent_dir)
		return (NULL);
	tmp = path;
	path = ft_strjoin_free(parent_dir, path);
	free(tmp);
	ft_putendl_fd(path, 2);
	return (path);
}

char	*build_relativ_from_working(char *path)
{
	char	*cwd;
	char	*path;

	if (!path)
		return (NULL);
	cwd = getcwd(NULL, 0);
		return 
	
}

char	*build_relativ_from_tilde(char *path)
{

}
