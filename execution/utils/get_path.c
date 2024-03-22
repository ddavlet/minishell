#include "../execution.h"

char	*get_path(char *name, char *envp[])
{
	if (ft_strchr(name, '/') == NULL)
		return (build_path_from_env(name));
	else if (name[0] == '/')
		return (name);
	else
		return (build_path_from_relative(name));
}

char	*build_path_from_relative(char *relative_path)
{
    t_path  *path;

    path = initialize_path(relative_path);

	path_abs = NULL;
    while (is_relative(path_abs))
    {

    }

	if (ft_strncmp(path, "../", 3) == 0)
		path_abs = build_relativ_from_parent(path);
	else if (ft_strncmp(path, "./", 2) == 0)
		path_abs = build_relativ_from_working(path);
	else if (ft_strncmp(path, "~/", 2) == 0)
		path_abs = build_relativ_from_tilde(path);
	else
		return (NULL);
}